#include "stdafx.h"
#include "Player.h"
#include "Stage/Object/Crystal.h"

namespace
{
	const float RUN_SPEED = 2.5f;					// �_�b�V�����̈ړ����x
	const float WALKING_SPEED = 1.0f;				// �����Ă��鎞�̈ړ����x

	const float DECREASE_STAMINA_VALUE = 15.0f;		// �_�b�V�����̃X�^�~�i����x
	const float INCREASE_STAMINA_VALUE = 10.0f;		// �X�^�~�i�񕜑��x

	const float LINEAR_COMPLETION = 1.0f;			// ���`�⊮

	const float Y_POSITION = 25.0f;					// �Փ˔��莞��Y���W

	const int	STAMINA_MIN = 1;					// �X�^�~�i�̍Œ�l
	const int	STAMINA_MAX = STAMINA;				// �X�^�~�i�̍ő�l
}

Player::Player() 
{
}

Player::~Player()
{
}

bool Player::Start()
{
	// �C���X�^���X��T��
	m_crystal = FindGO<Crystal>("crystal");

	LoadAnimation();

	m_modelRender.Init("Assets/modelData/player/unityChan.tkm", m_enAnimationClips, m_en_AnimationClips_Num, enModelUpAxisY);
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
	if (m_playerStatus.m_hitPoint <= 0) {
		// ���S����
		Death();
		return;
	}

	// �X�^�~�i���ő�l�łȂ��@���@A�{�^�������͂���Ă��Ȃ��Ƃ�
	if (m_playerStatus.m_stamina < STAMINA_MAX && 
		m_actionState != m_enActionState_Run) {

		m_recoveryTimer -= g_gameTime->GetFrameDeltaTime();

		if (m_recoveryTimer <= 0.0f) {
			// �X�^�~�i�𑝂₷
			m_playerStatus.m_stamina += g_gameTime->GetFrameDeltaTime() * INCREASE_STAMINA_VALUE;
		}
	}
	else {
		m_recoveryTimer = RECOVERY_TIMER;		// �^�C�}�[�����Z�b�g
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
	m_enAnimationClips[m_en_AnimationClips_Idle].Load("Assets/animData/player/idle.tka");
	m_enAnimationClips[m_en_AnimationClips_Idle].SetLoopFlag(true);

	m_enAnimationClips[m_en_AnimationClips_Walk].Load("Assets/animData/player/walk.tka");
	m_enAnimationClips[m_en_AnimationClips_Walk].SetLoopFlag(true);

	m_enAnimationClips[m_en_AnimationClips_Run].Load("Assets/animData/player/run.tka");
	m_enAnimationClips[m_en_AnimationClips_Run].SetLoopFlag(true);

	//m_EnAnimationClips[m_en_AnimationClips_Dig].Load("Assets/animData/player/dig.tka");
	//m_EnAnimationClips[m_en_AnimationClips_Dig].SetLoopFlag(true);

	m_enAnimationClips[m_en_AnimationClips_Damage].Load("Assets/animData/player/damage.tka");
	m_enAnimationClips[m_en_AnimationClips_Damage].SetLoopFlag(false);

	m_enAnimationClips[m_en_AnimationClips_Death].Load("Assets/animData/player/KneelDown.tka");
	m_enAnimationClips[m_en_AnimationClips_Death].SetLoopFlag(false);

	m_enAnimationClips[m_en_AnimationClips_Clear].Load("Assets/animData/player/clear.tka");
	m_enAnimationClips[m_en_AnimationClips_Clear].SetLoopFlag(false);
}

void Player::PlayAnimation()
{
	switch (m_actionState) {
	case m_enActionState_Idle:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Idle, LINEAR_COMPLETION);
		break;
	case m_enActionState_Walk:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Walk, LINEAR_COMPLETION);
		break;
	case m_enActionState_Run:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Run, LINEAR_COMPLETION);
		break;
	case m_enActionState_Dig:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Dig, LINEAR_COMPLETION);
		break;
	case m_enActionState_Damage:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Damage, LINEAR_COMPLETION);
		break;
	case m_enActionState_Death:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Death, LINEAR_COMPLETION);
		break;
	case m_enActionState_Clear:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Clear, LINEAR_COMPLETION);
		break;
	}
}

void Player::Rotation()
{
	// �X�e�B�b�N�̓��͂���������
	if (fabsf(m_basicSpeed.x) >= 0.001 || fabsf(m_basicSpeed.z) >= 0.001) {
		//�@�L�����N�^�[�̕�����ς���
		m_rotation.SetRotationYFromDirectionXZ(m_basicSpeed);
		m_modelRender.SetRotaition(m_rotation);
	}
	else {
		// �Ȃ��ꍇ�͑ҋ@��Ԃɂ���
		m_actionState = m_enActionState_Idle;
	}
}

void Player::Move()
{
	m_basicSpeed.x = 0.0f;
	m_basicSpeed.z = 0.0f;

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

	if (g_pad[0]->IsPress(enButtonA) && m_playerStatus.m_stamina >= STAMINA_MIN) {
		if (m_actionState == m_enActionState_Idle) {
			return;
		}

		// �{�^���������Ă���ԃ_�b�V��
		m_actionState = m_enActionState_Run;

		// �X�^�~�i�����炷
		m_playerStatus.m_stamina -= g_gameTime->GetFrameDeltaTime() * DECREASE_STAMINA_VALUE;

		m_addSpped = RUN_SPEED;
	}
	else {
		// �����Ă��Ȃ��Ƃ��͕���
		m_actionState = m_enActionState_Walk;

		m_addSpped = WALKING_SPEED;
	}

	// �X�e�B�b�N�̓��͗ʁ~�ړ����x�~��Z���x�ōŏI�I�Ȉړ����x���v�Z����
	right *= stickL.x * m_playerStatus.m_basicSpeed * m_addSpped;
	forward *= stickL.y * m_playerStatus.m_basicSpeed * m_addSpped;

	// �ړ����x�ɏ�L�Ōv�Z�����x�N�g�������Z
	m_basicSpeed += right + forward;

	m_position = m_characterController.Execute(m_basicSpeed, 1.0f / 60.0f);

	m_modelRender.SetPosition(m_position);
}

void Player::Attack()
{
}

void Player::Damage(int attackPower)
{
	// �_���[�W���󂯂Ȃ���Ԃ̂Ƃ�
	if (m_canDamageflag == false) {
		// �ȉ��̏��������s���Ȃ�
		return;
	}

	m_en_AnimationClips_Damage;					// ��e���[�V�������Đ�

	m_playerStatus.m_hitPoint-= attackPower;	// �_���[�W�ʂ�HP�������
	m_canDamageflag = false;					// �A�����ă_���[�W���󂯂Ȃ�

	m_invincibleTimer -= g_gameTime->GetFrameDeltaTime();

	// �^�C�}�[��0.0f�ȉ��̂Ƃ�
	if (m_invincibleTimer < 0.0f) {
		m_canDamageflag = true;
		m_invincibleTimer = INVINCIBLE_TIMER;	// �^�C�}�[�����Z�b�g
	}
}

struct CrashedCrystal :public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;		// �Փ˃t���O

	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normallnWorldSpace) 
	{
		// �Փ˂��Ă��Ȃ�������
		if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Crystal) {
			return 0.0f;
		}
		
		isHit = true;
		return 0.0f;
	}
};

bool Player::HitCrstal(Vector3 position)
{
	btTransform start, end;

	start.setIdentity();
	end.setIdentity();

	// �n�_�ƏI�_��ݒ�
	start.setOrigin(btVector3(m_position.x, Y_POSITION, m_position.z));
	end.setOrigin(btVector3(position.x, Y_POSITION, position.z));

	CrashedCrystal callback;

	// �R���C�_�[���n�_����I�_�܂œ������ďՓ˂��������ׂ�
	PhysicsWorld::GetInstance()->ConvexSweepTest(
		(const btConvexShape*)m_sphereCollider.GetBody(),
		start, 
		end, 
		callback);

	// �Փ˂����Ȃ�false��Ԃ�
	if (callback.isHit) {
		return false;
	}

	return true;
}

void Player::Dig()
{
	if (HitCrstal(m_position) != true) {
		return;
	}

	// UI��\��

	if (g_pad[0]->IsPress(enButtonB)) {

		// UI�̃Q�[�W�𑝂₷

		m_actionState = m_enActionState_Dig;
	}

	//if()

	m_crystal->GetCrystal();					// �N���X�^�����擾
	int rarity = m_crystal->GetRarity();		// �擾�����N���X�^���̃��A�x���擾

	AddCrystalNum(rarity);						// list�ɒǉ�
}

void Player::Death()
{
	m_actionState = m_enActionState_Death;
}

void Player::Clear()
{
	m_actionState = m_enActionState_Clear;
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}