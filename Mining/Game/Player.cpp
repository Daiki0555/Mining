#include "stdafx.h"
#include "Player.h"
#include "Scene/Game.h"
#include "Stage/Object/Crystal.h"
#include "UI/PressAndHoldGauge.h"
#include "Stage/PhysicsGhost.h"

namespace
{
	const float DELTA_TIME = 1.0f / 60.0f;			// 経過時間

	const float RUN_SPEED = 2.5f;					// ダッシュ時の移動速度
	const float WALKING_SPEED = 1.0f;				// 歩いている時の移動速度

	const float DECREASE_STAMINA_VALUE = 15.0f;		// ダッシュ時のスタミナ消費速度
	const float INCREASE_STAMINA_VALUE = 10.0f;		// スタミナ回復速度

	const float LINEAR_COMPLETION = 1.0f;			// 線形補完

	const float Y_POSITION = 25.0f;					// 衝突判定時のY座標

	const float ADD_LENGTH = 0.5f;					// 加算する長さ
	const float NOT_DRAW_LENGTH = 100.0f;			// 描画しない長さ
	const float CAN_GET_LENGTH = 500.0f;			// 獲得できる距離

	const float CLEAR_LENGTH = 100.0f;				// クリアしたとみなされる距離

	const int	STAMINA_MIN = 1;					// スタミナの最低値
	const int	STAMINA_MAX = STAMINA;				// スタミナの最大値

	const int	HP_MIN = 0;							// HPの最低値
}

Player::Player() 
{
}

Player::~Player()
{
	m_haveCrystals.clear();

	for (int i = 0; i < m_haveCrystals.size(); i++) {
		DeleteGO(m_haveCrystals[i]);
	}
}

bool Player::Start()
{
	// インスタンスを探す
	m_game = FindGO<Game>("game");

	m_crystal = FindGO<Crystal>("crystal");
	m_pressAndHoldGauge = FindGO<PressAndHoldGauge>("pressAndHoldGauge");

	LoadAnimation();

	m_modelRender.Init("Assets/modelData/player/unityChan.tkm", m_enAnimationClips, m_en_AnimationClips_Num, enModelUpAxisY, true);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.SetScale(m_scale);

	m_characterController.Init(25.0f, 75.0f, m_position);	// キャラクターコントローラーを初期化

	// スフィアコライダーを設定
	m_sphereCollider.Create(20.0f);

	m_modelRender.Update();

	return true;
}

void Player::Update()
{
	// デバッグ用
	if (g_pad[0]->IsTrigger(enButtonStart)) {
	}

	if (m_actionState == m_enActionState_Clear) {
	}
	// 体力が0のとき
	else if (m_playerStatus.m_hitPoint <= HP_MIN) {

		// 補正
		m_playerStatus.m_hitPoint = HP_MIN;
		Death();				// 死亡する
	}
	else {
		Move();					// 移動
		Rotation();				// 回転
		IsClear();				// クリア判定

		// Bボタンが押されたとき
		if (g_pad[0]->IsPress(enButtonB)) {
			// 採掘する
			Dig();
		}
		else {
			// 角度を減らす
			m_pressAndHoldGauge->SetChangeGaugeAngle(false);

			// 円形ゲージの座標(Bボタンを押したときの自身の座標)へ向かうベクトルを作成
			Vector3 diff = m_pressAndHoldGauge->Get3DPosition() - m_position;

			if (m_pressAndHoldGauge->GetNowStatus() == m_pressAndHoldGauge->enGaugeState_Max ||
				diff.Length() >= NOT_DRAW_LENGTH) {
				// 円形ゲージをリセット
				m_pressAndHoldGauge->ResetGaugeAngle();
			}
		}

		// スタミナが最大値でない　かつ　Aボタンが入力されていないとき
		if (m_playerStatus.m_stamina < STAMINA_MAX &&
			m_actionState != m_enActionState_Run) {

			m_recoveryTimer -= g_gameTime->GetFrameDeltaTime();

			if (m_recoveryTimer <= 0.0f) {
				// スタミナを増やす
				m_playerStatus.m_stamina += g_gameTime->GetFrameDeltaTime() * INCREASE_STAMINA_VALUE;
			}
		}
		else {
			m_recoveryTimer = RECOVERY_TIMER;		// タイマーをリセット
		}
	}

	PlayAnimation();		// アニメーション

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.SetScale(m_scale);

	m_modelRender.Update();
}

void Player::LoadAnimation()
{
	m_enAnimationClips[m_en_AnimationClips_Idle].Load("Assets/animData/player/idle.tka");
	m_enAnimationClips[m_en_AnimationClips_Idle].SetLoopFlag(true);

	m_enAnimationClips[m_en_AnimationClips_Walk].Load("Assets/animData/player/walk.tka");
	m_enAnimationClips[m_en_AnimationClips_Walk].SetLoopFlag(true);

	m_enAnimationClips[m_en_AnimationClips_Run].Load("Assets/animData/player/run.tka");
	m_enAnimationClips[m_en_AnimationClips_Run].SetLoopFlag(true);

	m_enAnimationClips[m_en_AnimationClips_Damage].Load("Assets/animData/player/damage.tka");
	m_enAnimationClips[m_en_AnimationClips_Damage].SetLoopFlag(false);

	m_enAnimationClips[m_en_AnimationClips_Death].Load("Assets/animData/player/KneelDown.tka");
	m_enAnimationClips[m_en_AnimationClips_Death].SetLoopFlag(false);

	m_enAnimationClips[m_en_AnimationClips_Clear].Load("Assets/animData/player/clear.tka");
	m_enAnimationClips[m_en_AnimationClips_Clear].SetLoopFlag(false);
}

void Player::PlayAnimation()
{
	switch (m_actionState) {
	case m_enActionState_Idle:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Idle, LINEAR_COMPLETION);
		break;
	case m_enActionState_Walk:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Walk, LINEAR_COMPLETION);
		break;
	case m_enActionState_Run:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Run, LINEAR_COMPLETION);
		break;
	case m_enActionState_Dig:
		break;
	case m_enActionState_Damage:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Damage);
		break;
	case m_enActionState_Death:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Death, LINEAR_COMPLETION);
		break;
	case m_enActionState_Clear:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Clear, LINEAR_COMPLETION);
		break;
	}
}

void Player::Rotation()
{
	// スティックの入力があったら
	if (fabsf(m_basicSpeed.x) >= 0.001 || fabsf(m_basicSpeed.z) >= 0.001) {
		// キャラクターの方向を変える
		m_rotation.SetRotationYFromDirectionXZ(m_basicSpeed);
		m_modelRender.SetRotaition(m_rotation);
	}
	else {
		// ない場合は待機状態にする
		m_actionState = m_enActionState_Idle;
	}
}

void Player::Move()
{
	// ゲージが動いている間は動かさない
	if (m_pressAndHoldGauge->GetNowStatus() == m_pressAndHoldGauge->enGaugeState_Increase) {
		m_actionState = m_enActionState_Idle;
		return;
	}

	m_basicSpeed.x = 0.0f;
	m_basicSpeed.z = 0.0f;

	// ゲームパッドの入力量を参照する
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	// カメラの前方向と右方向のベクトルを持ってくる
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	// y方向には移動させない
	forward.y = 0.0f;
	right.y = 0.0f;

	if (g_pad[0]->IsPress(enButtonA) && m_playerStatus.m_stamina > STAMINA_MIN) {

		// スティックの入力があったとき
		if (fabsf(stickL.x) >= 0.001 || fabsf(stickL.y) >= 0.001) {
			// ボタンを押している間ダッシュ
			m_actionState = m_enActionState_Run;

			// スタミナを減らす
			//m_playerStatus.m_stamina -= g_gameTime->GetFrameDeltaTime() * DECREASE_STAMINA_VALUE;

			m_addValue += ADDSPEED;
			m_addSpped = min(m_addValue, RUN_SPEED);
		}
	}
	else {
		// 押していないときは歩く
		m_actionState = m_enActionState_Walk;

		m_addSpped = WALKING_SPEED;
	}

	// スティックの入力量×移動速度×乗算速度で最終的な移動速度を計算する
	right *= stickL.x * m_playerStatus.m_basicSpeed * m_addSpped;
	forward *= stickL.y * m_playerStatus.m_basicSpeed * m_addSpped;

	// 移動速度に上記で計算したベクトルを加算
	m_basicSpeed += right + forward;

	m_position = m_characterController.Execute(m_basicSpeed, DELTA_TIME);

	m_modelRender.SetPosition(m_position);
}

void Player::Attack()
{
}

void Player::Damage(int attackPower)
{
	// ダメージを受けられる状態のとき
	if (m_canAddDamage) {
		m_actionState = m_enActionState_Damage;
		m_playerStatus.m_hitPoint -= attackPower;			// ダメージ量をHPから引く
	
	
		m_canAddDamage = false;								// 連続してダメージを受けない
	}
	else {
		m_invincibleTimer -= g_gameTime->GetFrameDeltaTime();

		// タイマーが0.0f以下のとき
		if (m_invincibleTimer < 0.0f) {
			m_canAddDamage = true;
			m_invincibleTimer = INVINCIBLE_TIMER;			// タイマーをリセット
		}
	}
}

struct CrashedCrystal :public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;		// 衝突フラグ

	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normallnWorldSpace) 
	{
		// 衝突していなかったら
		if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Crystal) {
			return 0.0f;
		}
		
		isHit = true;
		return 0.0f;
	}
};

bool Player::CrystalAndHit(Vector3 targetPosition)
{
	btTransform start, end;

	start.setIdentity();
	end.setIdentity();

	// 始点と終点を設定
	start.setOrigin(btVector3(m_position.x, Y_POSITION, m_position.z));
	end.setOrigin(btVector3(targetPosition.x, Y_POSITION, targetPosition.z));

	CrashedCrystal callback;

	// コライダーを始点から終点まで動かして衝突したか調べる
	PhysicsWorld::GetInstance()->ConvexSweepTest(
		(const btConvexShape*)m_sphereCollider.GetBody(),
		start, 
		end, 
		callback);

	// 衝突したならfalseを返す
	if (callback.isHit) {
		return false;
	}

	return true;
}

void Player::Dig()
{
	Vector3 diff = Vector3::Zero;

	if (!m_isDig) {
		// クリスタルの母数を取得
		int crystalNum = m_game->GetCrystalList().size();

		for (int i = 0; i < crystalNum; i++) {

			if (m_isDig) {
				m_isDig = false;
				return;
			}

			if (m_game->GetCrystalList()[i]->GetCrystalState() != m_game->GetCrystalList()[i]->m_enCrystalStete_Normal) {
				continue;
			}

			// 座標を取得
			Vector3 crystalPos = m_game->GetCrystalList()[i]->GetPosition();
			// 自身の座標からクリスタルへ向かうベクトルを作成
			diff = crystalPos - m_position;

			// 衝突しているなら
			if (!CrystalAndHit(m_position + (diff * ADD_LENGTH))) {
				// 円形ゲージを描画する
				m_pressAndHoldGauge->SetCanDrawGauge(true);
				// 自身の座標を教える
				m_pressAndHoldGauge->Set3DPosition(m_position);
				// クリスタルを保存
				m_getCrystal = m_game->GetCrystalList()[i];
				m_crystalPosition = crystalPos;
				// 角度を増やす
				m_pressAndHoldGauge->SetChangeGaugeAngle(true);
				m_isDig = true;
				break;
			}

			// 円形ゲージを描画する
			m_pressAndHoldGauge->SetCanDrawGauge(false);
		}
	}
	else {
		// 自身の座標からクリスタルへ向かうベクトルを作成
		diff = m_crystalPosition - m_position;

		// 一定以上離れたら
		if (diff.Length() >= CAN_GET_LENGTH) {
			// 採掘しない
			m_isDig = false;
			return;
		}

		// ゲージが最大でないとき以下の処理は実行しない
		if (m_pressAndHoldGauge->GetNowStatus() != m_pressAndHoldGauge->enGaugeState_Min) {
			return;
		}

		//m_game->GetCrystalList().erase(
		//	std::remove(m_game->GetCrystalList().begin(), m_game->GetCrystalList().end(),m_getCrystal),
		//	m_game->GetCrystalList().end()
		//);

		//while (it != m_game->GetCrystalList().end()) {
		//	if (*it == m_getCrystal) {
		//		it = m_game->GetCrystalList().erase(it);
		//	}
		//	else {
		//		it++;
		//	}
		//}

		// 獲得処理
		m_getCrystal->SetCrystalState(m_crystal->m_enCrystalStete_HavePlayer);
		m_haveCrystals.push_back(m_getCrystal);

		// 円形ゲージをリセットする
		m_pressAndHoldGauge->ResetGaugeAngle();

		m_getCrystal = nullptr;
	}
}

void Player::IsClear()
{
	for (int i = 0; i < m_game->GetGhostList().size(); i++) {
		// クリア座標へ向かうベクトルを作成
		Vector3 diff = m_game->GetGhostList()[i]->GetPosition() - m_position;
		
		if (diff.Length() <= CLEAR_LENGTH) {
			Clear();
		}
	}
}

void Player::Death()
{
	m_actionState = m_enActionState_Death;
}

void Player::Clear()
{
	m_actionState = m_enActionState_Clear;
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}