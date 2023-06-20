#include "stdafx.h"
#include "Enemy_Mushroom.h"

namespace
{
	const int	ATTACK_POWER = 12;							// �U��
	const float BASIC_SPEED = 20.0f;						// ��{�X�s�[�h

	const float CHARACTERCONTROLLER_RADIUS = 50.0f;			// ���a
	const float CHARACTERCONTROLLER_HEIGHT = 50.0f;			// ����

	const float LINEAR_COMPLETION = 1.0f;					// ���`�⊮
}

Enemy_Mushroom::Enemy_Mushroom()
{
}

Enemy_Mushroom::~Enemy_Mushroom()
{
}

bool Enemy_Mushroom::Start()
{
	LoadAnimation();

	m_modelRender.Init("Assets/modelData/enemy/MushroomMan/MushroomMan.tkm", m_enAnimationClips, m_enAnimationClips_Num, enModelUpAxisZ);

	EnemyBasic::Start(
		ATTACK_POWER,					// �U����
		BASIC_SPEED,					// ��{�X�s�[�h
		CHARACTERCONTROLLER_RADIUS,		// �L�����N�^�[�R���g���[���[�̔��a
		CHARACTERCONTROLLER_HEIGHT		// �L�����N�^�[�R���g���[���[�̍���
	);

	return true;
}

void Enemy_Mushroom::LoadAnimation()
{
	m_enAnimationClips[m_enAnimationClips_Idle].Load("Assets/animData/enemy/MushroomManAnim/MushroomMonster_Idle.tka");
	m_enAnimationClips[m_enAnimationClips_Idle].SetLoopFlag(true);

	m_enAnimationClips[m_enAnimationClips_Move].Load("Assets/animData/enemy/MushroomManAnim/MushroomMonster_Walk.tka");
	m_enAnimationClips[m_enAnimationClips_Move].SetLoopFlag(true);

	m_enAnimationClips[m_enAnimationClips_Attack].Load("Assets/animData/enemy/MushroomManAnim/MushroomMonster_Attack.tka");
	m_enAnimationClips[m_enAnimationClips_Attack].SetLoopFlag(false);

	m_enAnimationClips[m_enAnimationClips_Damage].Load("Assets/animData/enemy/MushroomManAnim/MushroomMonster_Damage.tka");
	m_enAnimationClips[m_enAnimationClips_Damage].SetLoopFlag(false);
}

void Enemy_Mushroom::PlayAnimation()
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

void Enemy_Mushroom::Update()
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

void Enemy_Mushroom::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}