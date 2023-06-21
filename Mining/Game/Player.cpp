#include "stdafx.h"
#include "Player.h"
#include "Stage/Object/Crystal.h"

namespace
{
	const float RUN_SPEED = 2.5f;					// ダッシュ時の移動速度
	const float WALKING_SPEED = 1.0f;				// 歩いている時の移動速度

	const float DECREASE_STAMINA_VALUE = 15.0f;		// ダッシュ時のスタミナ消費速度
	const float INCREASE_STAMINA_VALUE = 10.0f;		// スタミナ回復速度

	const float LINEAR_COMPLETION = 1.0f;			// 線形補完

	const float Y_POSITION = 25.0f;					// 衝突判定時のY座標

	const int	STAMINA_MIN = 1;					// スタミナの最低値
	const int	STAMINA_MAX = STAMINA;				// スタミナの最大値
}

Player::Player() 
{
}

Player::~Player()
{
}

bool Player::Start()
{
	// インスタンスを探す
	m_crystal = FindGO<Crystal>("crystal");

	LoadAnimation();

	m_modelRender.Init("Assets/modelData/player/unityChan.tkm", m_enAnimationClips, m_en_AnimationClips_Num, enModelUpAxisY);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.SetScale(m_scale);

	m_characterController.Init(25.0f, 75.0f, m_position);	// キャラクターコントローラーを初期化

	m_modelRender.Update();

	return true;
}

void Player::Update()
{
	// 体力が0のとき
	if (m_playerStatus.m_hitPoint <= 0) {
		// 死亡する
		Death();
		return;
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


	Move();					// 移動
	Rotation();				// 回転

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

	//m_EnAnimationClips[m_en_AnimationClips_Dig].Load("Assets/animData/player/dig.tka");
	//m_EnAnimationClips[m_en_AnimationClips_Dig].SetLoopFlag(true);

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
		m_modelRender.PlayAnimation(m_en_AnimationClips_Dig, LINEAR_COMPLETION);
		break;
	case m_enActionState_Damage:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Damage, LINEAR_COMPLETION);
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
		//　キャラクターの方向を変える
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

	if (g_pad[0]->IsPress(enButtonA) && m_playerStatus.m_stamina >= STAMINA_MIN) {
		if (m_actionState == m_enActionState_Idle) {
			return;
		}

		// ボタンを押している間ダッシュ
		m_actionState = m_enActionState_Run;

		// スタミナを減らす
		m_playerStatus.m_stamina -= g_gameTime->GetFrameDeltaTime() * DECREASE_STAMINA_VALUE;

		m_addSpped = RUN_SPEED;
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

	m_position = m_characterController.Execute(m_basicSpeed, 1.0f / 60.0f);

	m_modelRender.SetPosition(m_position);
}

void Player::Attack()
{
}

void Player::Damage(int attackPower)
{
	// ダメージを受けない状態のとき
	if (m_canDamageflag == false) {
		// 以下の処理を実行しない
		return;
	}

	m_en_AnimationClips_Damage;					// 被弾モーションを再生

	m_playerStatus.m_hitPoint-= attackPower;	// ダメージ量をHPから引く
	m_canDamageflag = false;					// 連続してダメージを受けない

	m_invincibleTimer -= g_gameTime->GetFrameDeltaTime();

	// タイマーが0.0f以下のとき
	if (m_invincibleTimer < 0.0f) {
		m_canDamageflag = true;
		m_invincibleTimer = INVINCIBLE_TIMER;	// タイマーをリセット
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

bool Player::HitCrstal(Vector3 position)
{
	btTransform start, end;

	start.setIdentity();
	end.setIdentity();

	// 始点と終点を設定
	start.setOrigin(btVector3(m_position.x, Y_POSITION, m_position.z));
	end.setOrigin(btVector3(position.x, Y_POSITION, position.z));

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
	if (HitCrstal(m_position) != true) {
		return;
	}

	// UIを表示

	if (g_pad[0]->IsPress(enButtonB)) {

		// UIのゲージを増やす

		m_actionState = m_enActionState_Dig;
	}

	//if()

	m_crystal->GetCrystal();					// クリスタルを取得
	int rarity = m_crystal->GetRarity();		// 取得したクリスタルのレア度を取得

	AddCrystalNum(rarity);						// listに追加
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