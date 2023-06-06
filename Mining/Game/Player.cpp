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
	m_ModelRender.Init("Assets/modelData/player/unityChan.tkm", m_EnAnimationClips, m_en_AnimationClips_Num, enModelUpAxisY);
	m_ModelRender.SetPosition(m_Position);
	m_ModelRender.SetRotaition(m_Rotation);
	m_ModelRender.SetScale(m_Scale);

	m_ModelRender.Update();
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

void Player::Rotation(Vector3 rotation)
{

}

void Player::Move()
{

}

void Player::Attack()
{

}

void Player::Damage(float attackPower)
{

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