#include "stdafx.h"
#include "Enemy_Slime.h"

namespace
{
	const int		ATTACK_POWER = 30;							// 攻撃
	const float		BASIC_SPEED = 150.0f;						// 基本スピード

	const Vector3	SCALE = { 5.0f,5.0f,5.0f };					// スケール

	const float		CHARACTERCONTROLLER_RADIUS = 50.0f;			// 半径
	const float		CHARACTERCONTROLLER_HEIGHT = 50.0f;			// 高さ

	const float		LINEAR_COMPLETION = 1.0f;					// 線形補完
}

Enemy_Slime::Enemy_Slime()
{
}

Enemy_Slime::~Enemy_Slime()
{
}

bool Enemy_Slime::Start()
{
	LoadAnimation();

	m_scale = SCALE;

	m_modelRender.Init("Assets/modelData/enemy/SlimeRabbit/SlimeRabbit.tkm", m_enAnimationClips, m_enAnimationClips_Num, enModelUpAxisZ, true);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();

	EnemyBasic::Start(
		ATTACK_POWER,					// 攻撃力
		BASIC_SPEED,					// 基本スピード
		CHARACTERCONTROLLER_RADIUS,		// キャラクターコントローラーの半径
		CHARACTERCONTROLLER_HEIGHT		// キャラクターコントローラーの高さ
	);

	return true;
}

void Enemy_Slime::LoadAnimation()
{
	// Attackなし
	m_enAnimationClips[m_enAnimationClips_Idle].Load("Assets/animData/enemy/SlimeRabbitAnim/SlimeRabbit_Idle.tka");
	m_enAnimationClips[m_enAnimationClips_Idle].SetLoopFlag(true);

	m_enAnimationClips[m_enAnimationClips_Move].Load("Assets/animData/enemy/SlimeRabbitAnim/SlimeRabbit_Move.tka");
	m_enAnimationClips[m_enAnimationClips_Move].SetLoopFlag(true);
}

void Enemy_Slime::PlayAnimation()
{
	switch (m_actionState) {
	case m_enActionState_Idle:
	case m_enActionState_StopAction:
		m_modelRender.PlayAnimation(m_enAnimationClips_Idle, LINEAR_COMPLETION);
		break;
	case m_enActionState_Move:
	case m_enActionState_Attack:
		m_modelRender.PlayAnimation(m_enAnimationClips_Move, LINEAR_COMPLETION);
		break;
	}
}

void Enemy_Slime::Action()
{
	switch (m_actionState) {
	case m_enActionState_Idle:
		Idle();
		break;
	case m_enActionState_Move:
		Move();
		break;
	case m_enActionState_Attack:
		Attack();
		break;
	case m_enActionState_StopAction:
		StopAction();
		break;
	}
}

void Enemy_Slime::Update()
{
	Action();
	PlayAnimation();

	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Enemy_Slime::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}