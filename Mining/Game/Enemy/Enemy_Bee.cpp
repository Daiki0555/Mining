#include "stdafx.h"
#include "Enemy_Bee.h"

namespace
{
	const int	ATTACK_POWER = 5;							// �U��
	const float BASIC_SPEED = 50.0f;						// ��{�X�s�[�h

	const float CHARACTERCONTROLLER_RADIUS = 50.0f;			// ���a
	const float CHARACTERCONTROLLER_HEIGHT = 50.0f;			// ����
}

Enemy_Bee::Enemy_Bee()
{
}

Enemy_Bee::~Enemy_Bee()
{
}

bool Enemy_Bee::Start()
{
	m_modelRender.Init("Assets/modelData/enemy/MushroomMan/MushroomMan.tkm", m_EnanimationClips, m_en_AnimationClips_Num, enModelUpAxisZ);

	EnemyBasic::Start(
		ATTACK_POWER,					// �U����
		BASIC_SPEED,					// ��{�X�s�[�h
		CHARACTERCONTROLLER_RADIUS,		// �L�����N�^�[�R���g���[���[�̔��a
		CHARACTERCONTROLLER_HEIGHT		// �L�����N�^�[�R���g���[���[�̍���
	);

	return true;
}

void Enemy_Bee::LoadAnimation()
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

void Enemy_Bee::PlayAnimation()
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

void Enemy_Bee::Update()
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

void Enemy_Bee::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}