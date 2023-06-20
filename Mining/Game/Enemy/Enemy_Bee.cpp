#include "stdafx.h"
#include "Enemy_Bee.h"

namespace
{
	const int	ATTACK_POWER = 5;							// 攻撃
	const float BASIC_SPEED = 50.0f;						// 基本スピード

	const float Y_UP = 50.0f;								// 地面から浮かせる値

	const float CHARACTERCONTROLLER_RADIUS = 15.0f;			// 半径
	const float CHARACTERCONTROLLER_HEIGHT = 15.0f;			// 高さ

	const float LINEAR_COMPLETION = 1.0f;					// 線形補完
}

Enemy_Bee::Enemy_Bee()
{
}

Enemy_Bee::~Enemy_Bee()
{
}

bool Enemy_Bee::Start()
{
	LoadAnimation();

	m_modelRender.Init("Assets/modelData/enemy/bee/bee.tkm", m_enAnimationClips, m_enAnimationClips_Num, enModelUpAxisZ);

	EnemyBasic::Start(
		ATTACK_POWER,					// 攻撃力
		BASIC_SPEED,					// 基本スピード
		CHARACTERCONTROLLER_RADIUS,		// キャラクターコントローラーの半径
		CHARACTERCONTROLLER_HEIGHT		// キャラクターコントローラーの高さ
	);

	m_position.y += Y_UP;				// 浮かせる

	return true;
}

void Enemy_Bee::LoadAnimation()
{
	m_enAnimationClips[m_enAnimationClips_Idle].Load("Assets/animData/enemy/bee/idle.tka");
	m_enAnimationClips[m_enAnimationClips_Idle].SetLoopFlag(true);

	m_enAnimationClips[m_enAnimationClips_Move].Load("Assets/animData/enemy/bee/move.tka");
	m_enAnimationClips[m_enAnimationClips_Move].SetLoopFlag(true);

	m_enAnimationClips[m_enAnimationClips_Attack].Load("Assets/animData/enemy/bee/attack.tka");
	m_enAnimationClips[m_enAnimationClips_Attack].SetLoopFlag(false);

	m_enAnimationClips[m_enAnimationClips_Damage].Load("Assets/animData/enemy/bee/damage.tka");
	m_enAnimationClips[m_enAnimationClips_Damage].SetLoopFlag(false);
}

void Enemy_Bee::PlayAnimation()
{
	switch (m_actionState) {
	case m_enActionState_Idle:
		m_modelRender.PlayAnimation(m_enAnimationClips_Idle, LINEAR_COMPLETION);
		break;
	case m_enActionState_Move:
		m_modelRender.PlayAnimation(m_enAnimationClips_Move, LINEAR_COMPLETION);
		break;
	case m_enActionState_Attack:
		m_modelRender.PlayAnimation(m_enAnimationClips_Attack, LINEAR_COMPLETION);
		break;
	case m_enActionState_Damage:
		m_modelRender.PlayAnimation(m_enAnimationClips_Damage, LINEAR_COMPLETION);
		break;
	}
}

void Enemy_Bee::Update()
{
	switch (m_actionState) {
	case m_enActionState_Idle:
		break;
	case m_enActionState_Move:
		break;
	case m_enActionState_Attack:
		break;
	case m_enActionState_Damage:
		break;
	}

	PlayAnimation();

	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Enemy_Bee::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}