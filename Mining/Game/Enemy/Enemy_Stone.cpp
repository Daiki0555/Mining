#include "stdafx.h"
#include "Enemy_Stone.h"

namespace
{
	const int		ATTACK_POWER = 10;							// �U��
	const float		BASIC_SPEED = 200.0f;						// ��{�X�s�[�h

	const Vector3	SCALE = { 1.5f,1.5f,1.5f };					// �X�P�[��
	const float		Y_UP = 80.0f;								// �n�ʂ��畂������l

	const float		CHARACTERCONTROLLER_RADIUS = 15.0f;			// ���a
	const float		CHARACTERCONTROLLER_HEIGHT = 15.0f;			// ����

	const float		LINEAR_COMPLETION = 1.0f;					// ���`�⊮
}

Enemy_Stone::Enemy_Stone()
{
}

Enemy_Stone::~Enemy_Stone()
{
}

bool Enemy_Stone::Start()
{
	LoadAnimation();

	m_scale = SCALE;
	m_position.y += Y_UP;				// ��������

	m_modelRender.Init("Assets/modelData/enemy/StoneMonster/StoneMonster.tkm", m_enAnimationClips, m_enAnimationClips_Num, enModelUpAxisZ, true);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();

	EnemyBasic::Start(
		ATTACK_POWER,					// �U����
		BASIC_SPEED,					// ��{�X�s�[�h
		CHARACTERCONTROLLER_RADIUS,		// �L�����N�^�[�R���g���[���[�̔��a
		CHARACTERCONTROLLER_HEIGHT		// �L�����N�^�[�R���g���[���[�̍���
	);

	return true;
}

void Enemy_Stone::LoadAnimation()
{
	m_enAnimationClips[m_enAnimationClips_Idle].Load("Assets/animData/enemy/StoneMonsterAnim/StoneMonstorIdle.tka");
	m_enAnimationClips[m_enAnimationClips_Idle].SetLoopFlag(true);

	m_enAnimationClips[m_enAnimationClips_Move].Load("Assets/animData/enemy/StoneMonsterAnim/StoneMonstorRun.tka");
	m_enAnimationClips[m_enAnimationClips_Move].SetLoopFlag(true);

	m_enAnimationClips[m_enAnimationClips_Attack].Load("Assets/animData/enemy/StoneMonsterAnim/StoneMonstorAttack.tka");
	m_enAnimationClips[m_enAnimationClips_Attack].SetLoopFlag(false);
}

void Enemy_Stone::PlayAnimation()
{
	switch (m_actionState) {
	case m_enActionState_Idle:
	case m_enActionState_StopAction:
	case m_enActionState_GameQuit:
		m_modelRender.PlayAnimation(m_enAnimationClips_Idle, LINEAR_COMPLETION);
		break;
	case m_enActionState_Move:
		m_modelRender.PlayAnimation(m_enAnimationClips_Move, LINEAR_COMPLETION);
		break;
	case m_enActionState_Attack:
		m_modelRender.PlayAnimation(m_enAnimationClips_Attack, LINEAR_COMPLETION);
		break;
	}
}

void Enemy_Stone::Action()
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
	case m_enActionState_GameQuit:
		break;
	}
}

void Enemy_Stone::Update()
{
	Action();
	PlayAnimation();

	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Enemy_Stone::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}