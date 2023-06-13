#include "stdafx.h"
#include "Enemy_Slime.h"

namespace
{
	const int	ATTACK_POWER = 0;							// �U��
	const float BASIC_SPEED = 30.0f;						// ��{�X�s�[�h

	const float CHARACTERCONTROLLER_RADIUS = 50.0f;			// ���a
	const float CHARACTERCONTROLLER_HEIGHT = 50.0f;			// ����
}

Enemy_Slime::Enemy_Slime()
{
}

Enemy_Slime::~Enemy_Slime()
{
}

bool Enemy_Slime::Start()
{
	m_modelRender.Init("Assets/modelData/enemy/SlimeRabbit/SlimeRabbit.tkm", m_EnanimationClips, m_en_AnimationClips_Num, enModelUpAxisZ);

	EnemyBasic::Start(
		ATTACK_POWER,					// �U����
		BASIC_SPEED,					// ��{�X�s�[�h
		CHARACTERCONTROLLER_RADIUS,		// �L�����N�^�[�R���g���[���[�̔��a
		CHARACTERCONTROLLER_HEIGHT		// �L�����N�^�[�R���g���[���[�̍���
	);
}

void Enemy_Slime::LoadAnimation()
{
	// Attack�Ȃ�
	m_EnanimationClips[m_en_AnimationClips_Idle].Load("Assets/animData/enemy/SlimeRabbitAnim/SlimeRabbit_Idle.tka");
	m_EnanimationClips[m_en_AnimationClips_Idle].SetLoopFlag(true);

	m_EnanimationClips[m_en_AnimationClips_Move].Load("Assets/animData/enemy/SlimeRabbitAnim/SlimeRabbit_Move.tka");
	m_EnanimationClips[m_en_AnimationClips_Move].SetLoopFlag(true);

	m_EnanimationClips[m_en_AnimationClips_Damage].Load("Assets/animData/enemy/SlimeRabbitAnim/SlimeRabbit_Damage.tka");
	m_EnanimationClips[m_en_AnimationClips_Damage].SetLoopFlag(true);
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
}

void Enemy_Slime::Render(RenderContext& rc)
{

}