#include "stdafx.h"
#include "Player.h"

Player::Player() 
{
}

Player::~Player()
{
}

bool Player::Start()
{
	LoadAnimation();

	m_modelRender.Init("Assets/modelData/player/unityChan.tkm", m_EnAnimationClips, m_en_AnimationClips_Num, enModelUpAxisY);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.SetScale(m_scale);

	m_characterController.Init(25.0f, 75.0f, m_position);	// �L�����N�^�[�R���g���[���[��������

	m_modelRender.Update();

	return true;
}

void Player::Update()
{
	// �̗͂�0�̂Ƃ�
	if (playerStatus.m_hitPoint <= 0) {
		// ���S����
		Death();
		return;
	}

	Move();					// �ړ�
	Rotation();				// ��]

	PlayAnimation();		// �A�j���[�V����

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.SetScale(m_scale);

	m_modelRender.Update();
}

void Player::LoadAnimation()
{
	m_EnAnimationClips[m_en_AnimationClips_Idle].Load("Assets/animData/player/idle.tka");
	m_EnAnimationClips[m_en_AnimationClips_Idle].SetLoopFlag(true);

	m_EnAnimationClips[m_en_AnimationClips_Walk].Load("Assets/animData/player/walk.tka");
	m_EnAnimationClips[m_en_AnimationClips_Walk].SetLoopFlag(true);

	m_EnAnimationClips[m_en_AnimationClips_Run].Load("Assets/animData/player/run.tka");
	m_EnAnimationClips[m_en_AnimationClips_Run].SetLoopFlag(true);

	//m_EnAnimationClips[m_en_AnimationClips_Dig].Load("Assets/animData/player/dig.tka");
	//m_EnAnimationClips[m_en_AnimationClips_Dig].SetLoopFlag(true);

	m_EnAnimationClips[m_en_AnimationClips_Damage].Load("Assets/animData/player/damage.tka");
	m_EnAnimationClips[m_en_AnimationClips_Damage].SetLoopFlag(false);

	m_EnAnimationClips[m_en_AnimationClips_Death].Load("Assets/animData/player/KneelDown.tka");
	m_EnAnimationClips[m_en_AnimationClips_Death].SetLoopFlag(false);

	m_EnAnimationClips[m_en_AnimationClips_Clear].Load("Assets/animData/player/clear.tka");
	m_EnAnimationClips[m_en_AnimationClips_Clear].SetLoopFlag(false);
}

void Player::PlayAnimation()
{
	switch (m_actionState) {
	case m_ActionState_Idle:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Idle);
		break;
	case m_ActionState_Walk:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Walk);
		break;
	case m_ActionState_Run:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Run);
		break;
	case m_ActionState_Dig:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Dig);
		break;
	case m_ActionState_Damage:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Damage);
		break;
	case m_ActionState_Death:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Death);
		break;
	case m_ActionState_Clear:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Clear);
		break;
	}
}

void Player::Rotation()
{
	// �X�e�B�b�N�̓��͂���������
	if (fabsf(m_moveSpeed.x) >= 0.001 || fabsf(m_moveSpeed.z) >= 0.001) {
		//�@�L�����N�^�[�̕�����ς���
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		m_modelRender.SetRotaition(m_rotation);
	}
	else {
		// �Ȃ��ꍇ�͑ҋ@��Ԃɂ���
		m_actionState = m_ActionState_Idle;
	}
}

void Player::Move()
{
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	// �Q�[���p�b�h�̓��͗ʂ��Q�Ƃ���
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	// �J�����̑O�����ƉE�����̃x�N�g���������Ă���
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	// y�����ɂ͈ړ������Ȃ�
	forward.y = 0.0f;
	right.y = 0.0f;

	if (g_pad[0]->IsPress(enButtonA)) {
		// �{�^���������Ă���ԃ_�b�V��
		m_actionState = m_ActionState_Run;
		m_addSpped = 2.5f;
	}
	else {
		// �����Ă��Ȃ��Ƃ��͕���
		m_actionState = m_ActionState_Walk;
		m_addSpped = 1.0f;
	}

	// �X�e�B�b�N�̓��͗ʁ~�ړ����x�~��Z���x�ōŏI�I�Ȉړ����x���v�Z����
	right *= stickL.x * playerStatus.m_basicSpeed * m_addSpped;
	forward *= stickL.y * playerStatus.m_basicSpeed * m_addSpped;

	// �ړ����x�ɏ�L�Ōv�Z�����x�N�g�������Z
	m_moveSpeed += right + forward;

	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	m_modelRender.SetPosition(m_position);
}

void Player::Attack()
{
}

void Player::Damage(int attackPower)
{
	// �_���[�W���󂯂Ȃ���Ԃ̂Ƃ�
	if (m_takeDamageflag == false) {
		// �ȉ��̏��������s���Ȃ�
		return;
	}

	m_en_AnimationClips_Damage;					// ��e���[�V�������Đ�

	playerStatus.m_hitPoint-= attackPower;		// �_���[�W�ʂ�HP�������
	m_takeDamageflag = false;					// �A�����ă_���[�W���󂯂Ȃ�

	m_invincibleTimer -= g_gameTime->GetFrameDeltaTime();

	// �^�C�}�[��0.0f�ȉ��̂Ƃ�
	if (m_invincibleTimer < 0.0f) {
		m_takeDamageflag = true;
	}
}

void Player::Death()
{
	m_actionState = m_ActionState_Death;
}

void Player::Dig()
{
	m_actionState = m_ActionState_Dig;
}

void Player::Clear()
{
	m_actionState = m_ActionState_Clear;
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}