#include "stdafx.h"
#include "Enemy_Bee.h"

namespace
{
	const int	ATTACK_POWER = 5;							// �U��
	const float BASIC_SPEED = 50.0f;						// ��{�X�s�[�h

	const float CHARACTERCONTROLLER_RADIUS = 15.0f;			// ���a
	const float CHARACTERCONTROLLER_HEIGHT = 15.0f;			// ����

	const float LINEAR_COMPLETION = 1.0f;					// ���`�⊮
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

	m_modelRender.Init("Assets/modelData/enemy/bee/bee.tkm", m_EnanimationClips, m_en_AnimationClips_Num, enModelUpAxisZ);

	EnemyBasic::Start(
		ATTACK_POWER,					// �U����
		BASIC_SPEED,					// ��{�X�s�[�h
		CHARACTERCONTROLLER_RADIUS,		// �L�����N�^�[�R���g���[���[�̔��a
		CHARACTERCONTROLLER_HEIGHT		// �L�����N�^�[�R���g���[���[�̍���
	);

	m_position.y += 50.0f;				// ��������

	return true;
}

void Enemy_Bee::LoadAnimation()
{
	m_EnanimationClips[m_en_AnimationClips_Idle].Load("Assets/animData/enemy/bee/idle.tka");
	m_EnanimationClips[m_en_AnimationClips_Idle].SetLoopFlag(true);

	m_EnanimationClips[m_en_AnimationClips_Move].Load("Assets/animData/enemy/bee/move.tka");
	m_EnanimationClips[m_en_AnimationClips_Move].SetLoopFlag(true);

	m_EnanimationClips[m_en_AnimationClips_Attack].Load("Assets/animData/enemy/bee/attack.tka");
	m_EnanimationClips[m_en_AnimationClips_Attack].SetLoopFlag(false);

	m_EnanimationClips[m_en_AnimationClips_Damage].Load("Assets/animData/enemy/bee/damage.tka");
	m_EnanimationClips[m_en_AnimationClips_Damage].SetLoopFlag(false);
}

void Enemy_Bee::PlayAnimation()
{
	switch (m_actionState) {
	case m_ActionState_Idle:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Idle, LINEAR_COMPLETION);
		break;
	case m_ActionState_Move:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Move, LINEAR_COMPLETION);
		break;
	case m_ActionState_Attack:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Attack, LINEAR_COMPLETION);
		break;
	case m_ActionState_Damage:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Damage, LINEAR_COMPLETION);
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

	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Enemy_Bee::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}