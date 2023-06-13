#include "stdafx.h"
#include "Enemy_Mushroom.h"

namespace
{
	const int	ATTACK_POWER = 12;							// 攻撃
	const float BASIC_SPEED = 20.0f;						// 基本スピード

	const float CHARACTERCONTROLLER_RADIUS = 50.0f;			// 半径
	const float CHARACTERCONTROLLER_HEIGHT = 50.0f;			// 高さ
}

Enemy_Mushroom::Enemy_Mushroom()
{
}

Enemy_Mushroom::~Enemy_Mushroom()
{
}

bool Enemy_Mushroom::Start()
{
	m_modelRender.Init("Assets/modelData/enemy/MushroomMan/MushroomMan.tkm", m_EnanimationClips, m_en_AnimationClips_Num, enModelUpAxisZ);

	EnemyBasic::Start(
		ATTACK_POWER,					// 攻撃力
		BASIC_SPEED,					// 基本スピード
		CHARACTERCONTROLLER_RADIUS,		// キャラクターコントローラーの半径
		CHARACTERCONTROLLER_HEIGHT		// キャラクターコントローラーの高さ
	);
}

void Enemy_Mushroom::LoadAnimation()
{
	m_EnanimationClips[m_en_AnimationClips_Idle].Load("Assets/animData/enemy/MushroomManAnim/MushroomMan_Idle.tka");
	m_EnanimationClips[m_en_AnimationClips_Idle].SetLoopFlag(true);

	m_EnanimationClips[m_en_AnimationClips_Move].Load("Assets/animData/enemy/MushroomManAnim/MushroomMan_Move.tka");
	m_EnanimationClips[m_en_AnimationClips_Move].SetLoopFlag(true);

	m_EnanimationClips[m_en_AnimationClips_Attack].Load("Assets/animData/enemy/MushroomManAnim/MushroomMan_Attack.tka");
	m_EnanimationClips[m_en_AnimationClips_Attack].SetLoopFlag(true);

	m_EnanimationClips[m_en_AnimationClips_Damage].Load("Assets/animData/enemy/MushroomManAnim/MushroomMan_Damage.tka");
	m_EnanimationClips[m_en_AnimationClips_Damage].SetLoopFlag(true);
}

void Enemy_Mushroom::PlayAnimation()
{
	switch (m_actionState) {
	case m_ActionState_Idle:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Idle);
		break;
	case m_ActionState_Move:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Move);
		break;
	case m_ActionState_Attack:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Attack);
		break;
	case m_ActionState_Damage:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Damage);
		break;
	}
}

void Enemy_Mushroom::Update()
{
	switch (m_actionState) {
	case m_ActionState_Idle:
		break;
	case m_ActionState_Move:
		break;
	case m_ActionState_Attack:
		break;
	case m_ActionState_Damage:
		break;
	}

	PlayAnimation();
}

void Enemy_Mushroom::Update()
{

}

void Enemy_Mushroom::Render(RenderContext& rc)
{

}