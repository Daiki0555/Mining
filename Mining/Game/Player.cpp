#include "stdafx.h"
#include "Player.h"
#include "Scene/Game.h"
#include "Stage/Object/Crystal.h"
#include "UI/PressAndHoldGauge.h"

#define	DELTA_TIME 1.0f/60.0f						// �o�ߎ���

namespace
{
	const float RUN_SPEED = 2.5f;					// �_�b�V�����̈ړ����x
	const float WALKING_SPEED = 1.0f;				// �����Ă��鎞�̈ړ����x

	const float DECREASE_STAMINA_VALUE = 15.0f;		// �_�b�V�����̃X�^�~�i����x
	const float INCREASE_STAMINA_VALUE = 10.0f;		// �X�^�~�i�񕜑��x

	const float LINEAR_COMPLETION = 1.0f;			// ���`�⊮

	const float Y_POSITION = 25.0f;					// �Փ˔��莞��Y���W

	const float ADD_LENGTH = 50.0f;					// ���Z���钷��
	const float CANGET_LENGTH = 100.0f;				// �l���ł��钷��

	const int	STAMINA_MIN = 1;					// �X�^�~�i�̍Œ�l
	const int	STAMINA_MAX = STAMINA;				// �X�^�~�i�̍ő�l

	const int	HP_MIN = 0;							// HP�̍Œ�l
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
	m_game = FindGO<Game>("game");
	m_crystal = FindGO<Crystal>("crystal");
	m_pressAndHoldGauge = FindGO<PressAndHoldGauge>("pressAndHoldGauge");

	LoadAnimation();

	m_modelRender.Init("Assets/modelData/player/unityChan.tkm", m_enAnimationClips, m_en_AnimationClips_Num, enModelUpAxisY, true);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.SetScale(m_scale);

	m_characterController.Init(25.0f, 75.0f, m_position);	// �L�����N�^�[�R���g���[���[��������

	// �X�t�B�A�R���C�_�[��ݒ�
	m_sphereCollider.Create(10.0f);

	m_modelRender.Update();

	return true;
}

void Player::Update()
{
	//// �f�o�b�O�p
	//if (g_pad[0]->IsPress(enButtonA)) {
	//	m_playerStatus.m_hitPoint -= 5;
	//}

	// �̗͂�0�̂Ƃ�
	if (m_playerStatus.m_hitPoint <= HP_MIN) {

		// �␳
		m_playerStatus.m_hitPoint = HP_MIN;

		Death();				// ���S����
	}
	else {
		Move();					// �ړ�
		Rotation();				// ��]

		// B�{�^���������ꂽ�Ƃ�
		if (g_pad[0]->IsPress(enButtonB)) {
			// �̌@����
			Dig();
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
	}

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
		//m_modelRender.PlayAnimation(m_en_AnimationClips_Dig, LINEAR_COMPLETION);
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
	// �Q�[�W�������Ă���Ԃ͓������Ȃ�
	if (m_pressAndHoldGauge->GetNowStatus() == m_pressAndHoldGauge->enGaugeState_Increase) {
		return;
	}

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

	if (g_pad[0]->IsPress(enButtonA) && m_playerStatus.m_stamina > STAMINA_MIN) {

		// �X�e�B�b�N�̓��͂��������Ƃ�
		if (fabsf(stickL.x) >= 0.001 || fabsf(stickL.y) >= 0.001) {
			// �{�^���������Ă���ԃ_�b�V��
			m_actionState = m_enActionState_Run;

			// �X�^�~�i�����炷
			m_playerStatus.m_stamina -= g_gameTime->GetFrameDeltaTime() * DECREASE_STAMINA_VALUE;

			m_addSpped = RUN_SPEED;
		}
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

	m_position = m_characterController.Execute(m_basicSpeed, DELTA_TIME);

	m_modelRender.SetPosition(m_position);
}

void Player::Attack()
{
}

void Player::Damage(int attackPower)
{
	// �_���[�W���󂯂Ȃ���Ԃ̂Ƃ�
	if (m_canAddDamage == false) {
		// �ȉ��̏��������s���Ȃ�
		return;
	}

	m_en_AnimationClips_Damage;					// ��e���[�V�������Đ�

	m_playerStatus.m_hitPoint-= attackPower;	// �_���[�W�ʂ�HP�������
	m_canAddDamage = false;					// �A�����ă_���[�W���󂯂Ȃ�

	m_invincibleTimer -= g_gameTime->GetFrameDeltaTime();

	// �^�C�}�[��0.0f�ȉ��̂Ƃ�
	if (m_invincibleTimer < 0.0f) {
		m_canAddDamage = true;
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

bool Player::CrstalAndHit(Vector3 targetPosition)
{
	btTransform start, end;

	start.setIdentity();
	end.setIdentity();

	// �n�_�ƏI�_��ݒ�
	start.setOrigin(btVector3(m_position.x, Y_POSITION, m_position.z));
	end.setOrigin(btVector3(targetPosition.x, Y_POSITION, targetPosition.z));

	CrashedCrystal callback;

	// �R���C�_�[���n�_����I�_�܂œ������ďՓ˂��������ׂ�
	PhysicsWorld::GetInstance()->ConvexSweepTest(
		(const btConvexShape*)m_sphereCollider.GetBody(),
		start, 
		end, 
		callback);

	// �Փ˂����Ȃ�false��Ԃ�
	if (callback.isHit == true) {
		return false;
	}

	return true;
}

void Player::Dig()
{
	Vector3 diff = Vector3::Zero;
	int rarity = 0;
	int number = 0;

	if (!m_isDig) {
		// �N���X�^���̕ꐔ���擾
		int crystalNum = m_game->GetCrystalList().size();

		for (int i = 0; i < crystalNum; i++) {

			// ���W���擾
			Vector3 crystalPos = m_game->GetCrystalList()[i]->GetPosition();
			// ���g�̍��W����N���X�^���֌������x�N�g�����쐬
			diff = crystalPos - m_position;

			// �Փ˂��Ă��Ȃ��Ȃ璆�f
			if (CrstalAndHit(m_position + (diff * ADD_LENGTH))) {
				// �~�`�Q�[�W��`�悵�Ȃ�
				m_pressAndHoldGauge->SetCanDrawGauge(false);
				break;
			}

			// �~�`�Q�[�W��`�悷��
			m_pressAndHoldGauge->SetCanDrawGauge(true);
			// �~�`�Q�[�W��`�悷��
			m_pressAndHoldGauge->SetCanDrawGauge(true);
			// ���g�̍��W��������
			m_pressAndHoldGauge->Set3DPosition(m_position);
			// �N���X�^���̈ʒu��ۑ�
			m_crystalPosition = crystalPos;
			// ���A���e�B��ۑ�
			rarity = m_game->GetCrystalList()[i]->GetRarity();
			// �ԍ���ۑ�
			number = i;
			m_isDig = true;
		}
	}
	else {
		// ���g�̍��W����N���X�^���֌������x�N�g�����쐬
		diff = m_crystalPosition - m_position;

		// �Փ˂��Ă��Ȃ��Ȃ璆�f
		if (CrstalAndHit(m_position + (diff * ADD_LENGTH))) {
			// �~�`�Q�[�W��`�悵�Ȃ�
			m_pressAndHoldGauge->SetCanDrawGauge(false);
			// �̌@���Ȃ�
			m_isDig = false;
			return;
		}
		
		if (g_pad[0]->IsPress(enButtonB)) {
			// �p�x�𑝂₷
			m_pressAndHoldGauge->SetChangeGaugeAngle(true);
			m_actionState = m_enActionState_Dig;
		}
		else {
			// �p�x�����炷
			m_pressAndHoldGauge->SetChangeGaugeAngle(false);
		}

		// �Q�[�W���ő�łȂ��Ƃ��ȉ��̏����͎��s���Ȃ�
		if (m_pressAndHoldGauge->GetNowStatus() != m_pressAndHoldGauge->enGaugeState_Min) {
			return;
		}

		// �N���X�^�����擾����
		m_game->GetCrystalList()[number]->SetDrawFlag(false);
		//m_game->GetCrystalList().erase(m_game->GetCrystalList().begin() + number);
		// list�Ƀ��A���e�B��ǉ�
		AddCrystal(rarity);

		// �~�`�Q�[�W�����Z�b�g����
		m_pressAndHoldGauge->SetCanDrawGauge(false);
		m_pressAndHoldGauge->ResetGaugeAngle();
	}
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