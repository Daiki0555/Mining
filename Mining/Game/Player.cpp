#include "stdafx.h"
#include "Player.h"
#include "Scene/Game.h"
#include "Stage/Object/Crystal.h"
#include "UI/PressAndHoldGauge.h"
#include "Sound.h"

namespace
{
	const float DELTA_TIME = 1.0f / 60.0f;			// 1フレーム毎の時間
	const float RUN_SPEED = 5.0f;					// 走ったときの速度
	const float WALKING_SPEED = 2.5f;				// 歩いたときの速度
	const float DECREASE_STAMINA_VALUE = 15.0f;		// スタミナの減少値
	const float INCREASE_STAMINA_VALUE = 10.0f;		// スタミナの増加値
	const float LINEAR_COMPLETION = 1.0f;			// 線形補間率
	const float Y_POSITION = 25.0f;					// Y座標
	const float ADD_LENGTH = 0.5f;					// 追加する長さ
	const float NOT_DRAW_LENGTH = 100.0f;			// 描画しない長さ
	const float CAN_GET_LENGTH = 500.0f;			// クリスタルを獲得できる長さ
	const float CLEAR_LENGTH = 500.0f;				// クリアできる長さ
	const int	STAMINA_MIN = 1;					// スタミナの最低値
	const int	STAMINA_MAX = STAMINA;				// スタミナの最大値
	const int	HP_MIN = 0;							// HPの最小値
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
	m_sound = FindGO<Sound>("sound");

	LoadAnimation();

	m_modelRender.Init("Assets/modelData/player/unityChan.tkm", m_enAnimationClips, m_en_AnimationClips_Num, enModelUpAxisY, true);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.SetScale(m_scale);

	// キャラクターコントローラーを作成する
	m_characterController.Init(25.0f, 75.0f, m_position);
	// スフィアコライダーを作成する
	m_sphereCollider.Create(20.0f);

	m_modelRender.Update();

	return true;
}

void Player::Update()
{
	// クリア時の処理
	if (m_actionState == m_enActionState_Clear ) {
		if (m_modelRender.IsPlayingAnimation() == false) {
			m_game->SetIsEndAnimationFlag(true);
		}
	}
	// 死亡時の処理
	else if (m_actionState == m_enActionState_Death) {
		if (m_modelRender.IsPlayingAnimation() == false) {
			m_game->SetIsEndAnimationFlag(true);
		}
	}

	// ヒットポイントが最低値以下の場合
	else if (m_playerStatus.m_hitPoint <= HP_MIN) {
		// 死亡させる
		m_playerStatus.m_hitPoint = HP_MIN;
		m_actionState = m_enActionState_Death;
	}
	else {
		if (m_actionState == m_enActionState_Damage && m_modelRender.IsPlayingAnimation() == true) {
			PlayAnimation();

			m_modelRender.SetPosition(m_position);
			m_modelRender.SetRotaition(m_rotation);
			m_modelRender.SetScale(m_scale);

			m_modelRender.Update();
			return;
		}

		if (!m_canAddDamage) {
			m_invincibleTimer -= g_gameTime->GetFrameDeltaTime();

			// 無敵処理
			if (m_invincibleTimer < 0.0f) {
				m_canAddDamage = true;
				m_invincibleTimer = INVINCIBLE_TIMER;
			}
		}

		Move();
		Rotation();
		IsClear();

		// Bボタンが押されたとき
		if (g_pad[0]->IsPress(enButtonB)) {
			Dig();
		}
		else {
			// 角度は変更しない
			m_pressAndHoldGauge->SetChangeGaugeAngle(false);

			// 自身の座標からUIの座標へ向かうベクトル
			Vector3 diff = m_pressAndHoldGauge->Get3DPosition() - m_position;

			if (m_pressAndHoldGauge->GetNowStatus() == m_pressAndHoldGauge->enGaugeState_Max ||
				diff.Length() >= NOT_DRAW_LENGTH) {
				// 角度をリセット
				m_pressAndHoldGauge->ResetGaugeAngle();
			}
		}

		// スタミナが最大値以下　かつ　走っていない状態の時
		if (m_playerStatus.m_stamina < STAMINA_MAX &&
			m_actionState != m_enActionState_Run) {

			m_recoveryTimer -= g_gameTime->GetFrameDeltaTime();

			if (m_recoveryTimer <= 0.0f) {
				// スタミナを回復させる
				m_playerStatus.m_stamina += g_gameTime->GetFrameDeltaTime() * INCREASE_STAMINA_VALUE;
			}
		}
		else {
			m_recoveryTimer = RECOVERY_TIMER;
		}
	}

	PlayAnimation();

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
		m_modelRender.SetAnimationSpeed(0.5f);
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
	// 操作があったとき回転させる
	if (fabsf(m_basicSpeed.x) >= 0.001 || fabsf(m_basicSpeed.z) >= 0.001) {
		m_rotation.SetRotationYFromDirectionXZ(m_basicSpeed);
		m_modelRender.SetRotaition(m_rotation);
	}
	else {
		m_actionState = m_enActionState_Idle;
	}
}

void Player::Move()
{
	// ゲージが増加中なら待機
	if (m_pressAndHoldGauge->GetNowStatus() == m_pressAndHoldGauge->enGaugeState_Increase) {
		m_actionState = m_enActionState_Idle;
		return;
	}

	m_basicSpeed.x = 0.0f;
	m_basicSpeed.z = 0.0f;

	// スティックの値を参照する
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	// カメラの前方向と右方向を参照する
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	// yの値は使用しないため初期化する
	forward.y = 0.0f;
	right.y = 0.0f;

	if (g_pad[0]->IsPress(enButtonA) && m_playerStatus.m_stamina > STAMINA_MIN) {

		// 操作があったとき
		if (fabsf(stickL.x) >= 0.001 || fabsf(stickL.y) >= 0.001) {
			// 走らせる
			m_actionState = m_enActionState_Run;
			// スタミナを減らす
			m_playerStatus.m_stamina -= g_gameTime->GetFrameDeltaTime() * DECREASE_STAMINA_VALUE;
			// アニメーションを調整する
			m_addValue += ADDSPEED;
			m_addSpped = min(m_addValue, RUN_SPEED);
		}
	}
	else {
		m_actionState = m_enActionState_Walk;
		m_addSpped = WALKING_SPEED;
	}

	// 移動速度を計算する
	right *= stickL.x * m_playerStatus.m_basicSpeed * m_addSpped;
	forward *= stickL.y * m_playerStatus.m_basicSpeed * m_addSpped;

	// 最終的な移動速度に加算する
	m_basicSpeed += right + forward;

	m_position = m_characterController.Execute(m_basicSpeed, DELTA_TIME);

	m_modelRender.SetPosition(m_position);
}

void Player::Damage(int attackPower)
{
	if (!m_canAddDamage) {
		return;
	}

	m_actionState = m_enActionState_Damage;
	m_playerStatus.m_hitPoint -= attackPower;			// HPを減らす
	m_canAddDamage = false;								// すぐにはダメージを受けないようにする
}

struct CrashedCrystal :public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;		// 衝突フラグ

	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normallnWorldSpace) 
	{
		// 衝突しているのがクリスタルでないなら
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

	// 始点と終点を設定する
	start.setOrigin(btVector3(m_position.x, Y_POSITION, m_position.z));
	end.setOrigin(btVector3(targetPosition.x, Y_POSITION, targetPosition.z));

	CrashedCrystal callback;

	PhysicsWorld::GetInstance()->ConvexSweepTest(
		(const btConvexShape*)m_sphereCollider.GetBody(),
		start, 
		end, 
		callback);

	// 衝突しているなら
	if (callback.isHit) {
		return false;
	}

	return true;
}

void Player::Dig()
{
	Vector3 diff = Vector3::Zero;

	if (!m_isDig) {
		// 総数を取得する
		int crystalNum = m_game->GetCrystalList().size();

		for (int i = 0; i < crystalNum; i++) {

			if (m_isDig) {
				m_isDig = false;
				return;
			}

			if (m_game->GetCrystalList()[i]->GetCrystalState() != m_game->GetCrystalList()[i]->m_enCrystalStete_Normal) {
				continue;
			}

			// 座標を参照する
			Vector3 crystalPos = m_game->GetCrystalList()[i]->GetPosition();
			// 自身の座標からクリスタルへ向かうベクトル
			diff = crystalPos - m_position;

			// 衝突したなら
			if (!CrystalAndHit(m_position + (diff * ADD_LENGTH))) {
				// UIを描画する
				m_pressAndHoldGauge->SetCanDrawGauge(true);
				// UIの座標を設定
				m_pressAndHoldGauge->Set3DPosition(m_position);
				// 該当クリスタルのアドレスと座標を参照する
				m_getCrystal = m_game->GetCrystalList()[i];
				m_crystalPosition = crystalPos;
				// 角度を変化させる
				m_pressAndHoldGauge->SetChangeGaugeAngle(true);
				m_isDig = true;
				break;
			}

			// UIをびょうがしない
			m_pressAndHoldGauge->SetCanDrawGauge(false);
		}
	}
	else {
		// 自身の座標からクリスタルへ向かうベクトル
		diff = m_crystalPosition - m_position;

		// ベクトルの長さが一定以上のとき
		if (diff.Length() >= CAN_GET_LENGTH) {
			// 採掘を中断する
			m_isDig = false;
			return;
		}

		// ゲージが最小ならこれより以下の処理は実行しない
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

		m_sound->SetSoundSE(m_sound->m_enSoundState_GetSE);

		// 角度をリセットする
		m_pressAndHoldGauge->ResetGaugeAngle();

		m_getCrystal = nullptr;
	}
}

void Player::IsClear()
{
	for (int i = 0; i < m_game->GetGoalList().size(); i++) {
		// 自身の座標からゴールへ向かうベクトル
		Vector3 diff = m_game->GetGoalList()[i] - m_position;
		
		if (diff.Length() <= CLEAR_LENGTH) {
			m_actionState = m_enActionState_Clear;
		}
	}
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}