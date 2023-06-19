#include "stdafx.h"
#include "Enemy_Slime.h"

namespace
{
	const int	ATTACK_POWER = 0;							// 攻撃
	const float BASIC_SPEED = 30.0f;						// 基本スピード

	const float CHARACTERCONTROLLER_RADIUS = 50.0f;			// 半径
	const float CHARACTERCONTROLLER_HEIGHT = 50.0f;			// 高さ
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

	m_scale = { 5.0f,5.0f,5.0f };

	m_modelRender.Init("Assets/modelData/enemy/SlimeRabbit/SlimeRabbit.tkm", m_EnanimationClips, m_en_AnimationClips_Num, enModelUpAxisZ);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.SetPosition(m_position);

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
	m_EnanimationClips[m_en_AnimationClips_Idle].Load("Assets/animData/enemy/SlimeRabbitAnim/SlimeRabbit_Idle.tka");
	m_EnanimationClips[m_en_AnimationClips_Idle].SetLoopFlag(true);

	m_EnanimationClips[m_en_AnimationClips_Move].Load("Assets/animData/enemy/SlimeRabbitAnim/SlimeRabbit_Move.tka");
	m_EnanimationClips[m_en_AnimationClips_Move].SetLoopFlag(true);

	m_EnanimationClips[m_en_AnimationClips_Damage].Load("Assets/animData/enemy/SlimeRabbitAnim/SlimeRabbit_Damage.tka");
	m_EnanimationClips[m_en_AnimationClips_Damage].SetLoopFlag(false);
}

void Enemy_Slime::PlayAnimation()
{
	switch (m_actionState) {
	case m_ActionState_Idle:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Idle);
		break;
	case m_ActionState_Move:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Move);
		break;
	case m_ActionState_Damage:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Damage);
		break;
	}
}

void Enemy_Slime::Update()
{
	switch (m_actionState) {
	case m_ActionState_Idle:
		break;
	case m_ActionState_Move:
		break;
	case m_ActionState_Damage:
		break;
	}

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