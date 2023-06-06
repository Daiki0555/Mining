#include "stdafx.h"
#include "Player.h"

namespace 
{
	int			ATTACK_POWER = 50.0f;			// 攻撃力
	float		MOVE_SPEED = 100.0f;			// 移動速度
}

Player::Player() 
{

}

Player::~Player()
{

}

bool Player::Start()
{
	m_ModelRender.Init("Assets/modelData/player/unityChan.tkm", m_EnAnimationClips, m_en_AnimationClips_Num, enModelUpAxisY);
	m_ModelRender.SetPosition(m_Position);
	m_ModelRender.SetRotaition(m_Rotation);
	m_ModelRender.SetScale(m_Scale);

	m_CharacterController.Init(25.0f, 75.0f, m_Position);	// キャラクターコントローラーを初期化

	m_ModelRender.Update();

	return true;
}

void Player::Update()
{
	Move();



	m_ModelRender.SetPosition(m_Position);
	m_ModelRender.SetRotaition(m_Rotation);
	m_ModelRender.SetScale(m_Scale);

	m_ModelRender.Update();
}

void Player::LoadAnimation()
{

}

void Player::PlayAnimation()
{

}

void Player::Rotation()
{
	// スティックの入力があったら
	if (fabsf(m_MoveSpeed.x) >= 0.001 || fabsf(m_MoveSpeed.z) >= 0.001) {
		//　キャラクターの方向を変える
		m_Rotation.SetRotationYFromDirectionXZ(m_MoveSpeed);
		m_ModelRender.SetRotaition(m_Rotation);
	}
}

void Player::Move()
{
	m_MoveSpeed.x = 0.0f;
	m_MoveSpeed.y = 0.0f;

	// ゲームパッドの入力量を参照する
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	m_MoveSpeed.x += stickL.x * MOVE_SPEED;
	m_MoveSpeed.z += stickL.y * MOVE_SPEED;

	m_Position = m_CharacterController.Execute(m_MoveSpeed, 1.0f / 60.0f);

	m_ModelRender.SetPosition(m_Position);
}

void Player::Attack()
{
}

void Player::Damage(int attackPower)
{
	m_en_AnimationClips_Damage;

	m_HitPoint-= attackPower;
}

void Player::Death()
{

}

void Player::Dig()
{

}

void Player::Clear()
{

}

void Player::Render(RenderContext& rc)
{
	m_ModelRender.Draw(rc);
}