#include "stdafx.h"
#include "Enemy_Slime.h"

namespace
{
	const int	ATTACK_POWER = 0;							// �U��
	const float BASIC_SPEED = 30.0f;						// ��{�X�s�[�h

	const float CHARACTERCONTROLLER_RADIUS = 50.0f;			// ���a
	const float CHARACTERCONTROLLER_HEIGHT = 50.0f;			// ����

	const float LINEAR_COMPLETION = 1.0f;					// ���`�⊮
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

	m_modelRender.Init("Assets/modelData/enemy/SlimeRabbit/SlimeRabbit.tkm", m_enAnimationClips, m_enAnimationClips_Num, enModelUpAxisZ);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.SetPosition(m_position);

	EnemyBasic::Start(
		ATTACK_POWER,					// �U����
		BASIC_SPEED,					// ��{�X�s�[�h
		CHARACTERCONTROLLER_RADIUS,		// �L�����N�^�[�R���g���[���[�̔��a
		CHARACTERCONTROLLER_HEIGHT		// �L�����N�^�[�R���g���[���[�̍���
	);

	return true;
}

void Enemy_Slime::LoadAnimation()
{
	// Attack�Ȃ�
	m_enAnimationClips[m_enAnimationClips_Idle].Load("Assets/animData/enemy/SlimeRabbitAnim/SlimeRabbit_Idle.tka");
	m_enAnimationClips[m_enAnimationClips_Idle].SetLoopFlag(true);

	m_enAnimationClips[m_enAnimationClips_Move].Load("Assets/animData/enemy/SlimeRabbitAnim/SlimeRabbit_Move.tka");
	m_enAnimationClips[m_enAnimationClips_Move].SetLoopFlag(true);

	m_enAnimationClips[m_enAnimationClips_Damage].Load("Assets/animData/enemy/SlimeRabbitAnim/SlimeRabbit_Damage.tka");
	m_enAnimationClips[m_enAnimationClips_Damage].SetLoopFlag(false);
}

void Enemy_Slime::PlayAnimation()
{
	switch (m_actionState) {
	case m_enActionState_Idle:
		m_modelRender.PlayAnimation(m_enAnimationClips_Idle, LINEAR_COMPLETION);
		break;
	case m_enActionState_Move:
		m_modelRender.PlayAnimation(m_enAnimationClips_Move, LINEAR_COMPLETION);
		break;
	case m_enActionState_Damage:
		m_modelRender.PlayAnimation(m_enAnimationClips_Damage, LINEAR_COMPLETION);
		break;
	}
}

void Enemy_Slime::Update()
{
	switch (m_actionState) {
	case m_enActionState_Idle:
		break;
	case m_enActionState_Move:
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

void Enemy_Slime::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}