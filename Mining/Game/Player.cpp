#include "stdafx.h"
#include "Player.h"

Player::Player() 
{
}

Player::~Player()
{
}

bool Player::Start()
{
	LoadAnimation();

	m_modelRender.Init("Assets/modelData/player/unityChan.tkm", m_EnAnimationClips, m_en_AnimationClips_Num, enModelUpAxisY);
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
	if (playerStatus.m_hitPoint <= 0) {
		// 死亡する
		Death();
		return;
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
	m_EnAnimationClips[m_en_AnimationClips_Idle].Load("Assets/animData/player/idle.tka");
	m_EnAnimationClips[m_en_AnimationClips_Idle].SetLoopFlag(true);

	m_EnAnimationClips[m_en_AnimationClips_Walk].Load("Assets/animData/player/walk.tka");
	m_EnAnimationClips[m_en_AnimationClips_Walk].SetLoopFlag(true);

	m_EnAnimationClips[m_en_AnimationClips_Run].Load("Assets/animData/player/run.tka");
	m_EnAnimationClips[m_en_AnimationClips_Run].SetLoopFlag(true);

	//m_EnAnimationClips[m_en_AnimationClips_Dig].Load("Assets/animData/player/dig.tka");
	//m_EnAnimationClips[m_en_AnimationClips_Dig].SetLoopFlag(true);

	m_EnAnimationClips[m_en_AnimationClips_Damage].Load("Assets/animData/player/damage.tka");
	m_EnAnimationClips[m_en_AnimationClips_Damage].SetLoopFlag(false);

	m_EnAnimationClips[m_en_AnimationClips_Death].Load("Assets/animData/player/KneelDown.tka");
	m_EnAnimationClips[m_en_AnimationClips_Death].SetLoopFlag(false);

	m_EnAnimationClips[m_en_AnimationClips_Clear].Load("Assets/animData/player/clear.tka");
	m_EnAnimationClips[m_en_AnimationClips_Clear].SetLoopFlag(false);
}

void Player::PlayAnimation()
{
	switch (m_actionState) {
	case m_ActionState_Idle:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Idle);
		break;
	case m_ActionState_Walk:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Walk);
		break;
	case m_ActionState_Run:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Run);
		break;
	case m_ActionState_Dig:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Dig);
		break;
	case m_ActionState_Damage:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Damage);
		break;
	case m_ActionState_Death:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Death);
		break;
	case m_ActionState_Clear:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Clear);
		break;
	}
}

void Player::Rotation()
{
	// スティックの入力があったら
	if (fabsf(m_moveSpeed.x) >= 0.001 || fabsf(m_moveSpeed.z) >= 0.001) {
		//　キャラクターの方向を変える
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		m_modelRender.SetRotaition(m_rotation);
	}
	else {
		// ない場合は待機状態にする
		m_actionState = m_ActionState_Idle;
	}
}

void Player::Move()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

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

	if (g_pad[0]->IsPress(enButtonA)) {
		// ボタンを押している間ダッシュ
		m_actionState = m_ActionState_Run;
		m_addSpped = 2.5f;
	}
	else {
		// 押していないときは歩く
		m_actionState = m_ActionState_Walk;
		m_addSpped = 1.0f;
	}

	// スティックの入力量×移動速度×乗算速度で最終的な移動速度を計算する
	right *= stickL.x * playerStatus.m_basicSpeed * m_addSpped;
	forward *= stickL.y * playerStatus.m_basicSpeed * m_addSpped;

	// 移動速度に上記で計算したベクトルを加算
	m_moveSpeed += right + forward;

	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	m_modelRender.SetPosition(m_position);
}

void Player::Attack()
{
}

void Player::Damage(int attackPower)
{
	// ダメージを受けない状態のとき
	if (m_takeDamageflag == false) {
		// 以下の処理を実行しない
		return;
	}

	m_en_AnimationClips_Damage;					// 被弾モーションを再生

	playerStatus.m_hitPoint-= attackPower;		// ダメージ量をHPから引く
	m_takeDamageflag = false;					// 連続してダメージを受けない

	m_invincibleTimer -= g_gameTime->GetFrameDeltaTime();

	// タイマーが0.0f以下のとき
	if (m_invincibleTimer < 0.0f) {
		m_takeDamageflag = true;
	}
}

void Player::Death()
{
	m_actionState = m_ActionState_Death;
}

void Player::Dig()
{
	m_actionState = m_ActionState_Dig;
}

void Player::Clear()
{
	m_actionState = m_ActionState_Clear;
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}