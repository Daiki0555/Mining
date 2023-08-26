#include "stdafx.h"
#include "Player.h"
#include "Scene/Game.h"
#include "Stage/Object/Crystal.h"
#include "UI/PressAndHoldGauge.h"
#include "Sound.h"

namespace
{
	const float DELTA_TIME = 1.0f / 60.0f;			// �o�ߎ���
	const float RUN_SPEED = 2.5f;					// �_�b�V�����̈ړ����x
	const float WALKING_SPEED = 1.0f;				// ����Ă��鎞�̈ړ����x
	const float DECREASE_STAMINA_VALUE = 15.0f;		// �_�b�V�����̃X�^�~�i����x
	const float INCREASE_STAMINA_VALUE = 10.0f;		// �X�^�~�i�񕜑��x
	const float LINEAR_COMPLETION = 1.0f;			// ���`�⊮
	const float Y_POSITION = 25.0f;					// �Փ˔��莞��Y���W
	const float ADD_LENGTH = 0.5f;					// ���Z���钷��
	const float NOT_DRAW_LENGTH = 100.0f;			// �`�悵�Ȃ�����
	const float CAN_GET_LENGTH = 500.0f;			// �l���ł��鋗��
	const float CLEAR_LENGTH = 500.0f;				// �N���A�����Ƃ݂Ȃ���鋗��
	const int	STAMINA_MIN = 1;					// �X�^�~�i�̍Œ�l
	const int	STAMINA_MAX = STAMINA;				// �X�^�~�i�̍ő�l
	const int	HP_MIN = 0;							// HP�̍Œ�l
}

Player::Player() 
{
}

Player::~Player()
{
	m_haveCrystals.clear();

	for (int i = 0; i < m_haveCrystals.size(); i++) {
		DeleteGO(m_haveCrystals[i]);
	}
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

	m_characterController.Init(25.0f, 75.0f, m_position);	// �L�����N�^�[�R���g���[���[�������

	// �X�t�B�A�R���C�_�[��ݒ�
	m_sphereCollider.Create(20.0f);

	m_modelRender.Update();

	m_sound = FindGO<Sound>("sound");

	return true;
}

void Player::Update()
{
	//// �f�o�b�O�p
	//if (g_pad[0]->IsTrigger(enButtonStart)) {
	//	m_modelRender.PlayAnimation(m_enActionState_Damage);
	//}

	// �N���A�����Ƃ�
	if (m_actionState == m_enActionState_Clear ) {
		if (m_modelRender.IsPlayingAnimation() == false) {
			m_game->SetIsEndAnimationFlag(true);
		}
	}
	// ���S�����Ƃ�
	else if (m_actionState == m_enActionState_Death) {
		if (m_modelRender.IsPlayingAnimation() == false) {
			m_game->SetIsEndAnimationFlag(true);
		}
	}

	// �̗͂�0�̂Ƃ�
	else if (m_playerStatus.m_hitPoint <= HP_MIN) {

		// ���S����
		m_playerStatus.m_hitPoint = HP_MIN;		// �l��␳����
		m_actionState = m_enActionState_Death;
	}
	// �����łȂ��Ƃ�
	else {
		if (m_actionState == m_enActionState_Damage && m_modelRender.IsPlayingAnimation() == true) {
			PlayAnimation();		// �A�j���[�V����

			m_modelRender.SetPosition(m_position);
			m_modelRender.SetRotaition(m_rotation);
			m_modelRender.SetScale(m_scale);

			m_modelRender.Update();
			return;
		}

		if (!m_canAddDamage) {
			m_invincibleTimer -= g_gameTime->GetFrameDeltaTime();

			// �^�C�}�[��0.0f�ȉ��̂Ƃ�
			if (m_invincibleTimer < 0.0f) {
				m_canAddDamage = true;
				m_invincibleTimer = INVINCIBLE_TIMER;			// �^�C�}�[����Z�b�g
			}
		}

		Move();					// �ړ�
		Rotation();				// ��]
		IsClear();				// �N���A����

		// B�{�^���������ꂽ�Ƃ�
		if (g_pad[0]->IsPress(enButtonB)) {
			// �̌@����
			Dig();
		}
		else {
			// �p�x����炷
			m_pressAndHoldGauge->SetChangeGaugeAngle(false);

			// �~�`�Q�[�W�̍��W(B�{�^����������Ƃ��̎��g�̍��W)�֌������x�N�g����쐬
			Vector3 diff = m_pressAndHoldGauge->Get3DPosition() - m_position;

			if (m_pressAndHoldGauge->GetNowStatus() == m_pressAndHoldGauge->enGaugeState_Max ||
				diff.Length() >= NOT_DRAW_LENGTH) {
				// �~�`�Q�[�W����Z�b�g
				m_pressAndHoldGauge->ResetGaugeAngle();
			}
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
			m_recoveryTimer = RECOVERY_TIMER;		// �^�C�}�[����Z�b�g
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
		break;
	case m_enActionState_Damage:
		m_modelRender.PlayAnimation(m_en_AnimationClips_Damage);
		m_modelRender.SetAnimationSpeed(0.5f);
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
		// �L�����N�^�[�̕�����ς���
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
		m_actionState = m_enActionState_Idle;
		return;
	}

	m_basicSpeed.x = 0.0f;
	m_basicSpeed.z = 0.0f;

	// �Q�[���p�b�h�̓��͗ʂ�Q�Ƃ���
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	// �J�����̑O�����ƉE�����̃x�N�g��������Ă���
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	// y�����ɂ͈ړ������Ȃ�
	forward.y = 0.0f;
	right.y = 0.0f;

	if (g_pad[0]->IsPress(enButtonA) && m_playerStatus.m_stamina > STAMINA_MIN) {

		// �X�e�B�b�N�̓��͂��������Ƃ�
		if (fabsf(stickL.x) >= 0.001 || fabsf(stickL.y) >= 0.001) {
			// �{�^��������Ă���ԃ_�b�V��
			m_actionState = m_enActionState_Run;

			// �X�^�~�i����炷
			m_playerStatus.m_stamina -= g_gameTime->GetFrameDeltaTime() * DECREASE_STAMINA_VALUE;

			m_addValue += ADDSPEED;
			m_addSpped = min(m_addValue, RUN_SPEED);
		}
	}
	else {
		// �����Ă��Ȃ��Ƃ��͕��
		m_actionState = m_enActionState_Walk;

		m_addSpped = WALKING_SPEED;
	}

	// �X�e�B�b�N�̓��͗ʁ~�ړ����x�~��Z���x�ōŏI�I�Ȉړ����x��v�Z����
	right *= stickL.x * m_playerStatus.m_basicSpeed * m_addSpped;
	forward *= stickL.y * m_playerStatus.m_basicSpeed * m_addSpped;

	// �ړ����x�ɏ�L�Ōv�Z�����x�N�g������Z
	m_basicSpeed += right + forward;

	m_position = m_characterController.Execute(m_basicSpeed, DELTA_TIME);

	m_modelRender.SetPosition(m_position);
}

void Player::Damage(int attackPower)
{
	if (!m_canAddDamage) {
		return;
	}

	// �_���[�W��󂯂����Ԃ̂Ƃ�
	m_actionState = m_enActionState_Damage;
	m_playerStatus.m_hitPoint -= attackPower;			// �_���[�W�ʂ�HP�������
	m_canAddDamage = false;								// �A���Ń_���[�W��󂯂Ȃ��悤�ɐݒ�
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

bool Player::CrystalAndHit(Vector3 targetPosition)
{
	btTransform start, end;

	start.setIdentity();
	end.setIdentity();

	// �n�_�ƏI�_��ݒ�
	start.setOrigin(btVector3(m_position.x, Y_POSITION, m_position.z));
	end.setOrigin(btVector3(targetPosition.x, Y_POSITION, targetPosition.z));

	CrashedCrystal callback;

	// �R���C�_�[��n�_����I�_�܂œ������ďՓ˂��������ׂ�
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
	Vector3 diff = Vector3::Zero;

	if (!m_isDig) {
		// �N���X�^���̕ꐔ��擾
		int crystalNum = m_game->GetCrystalList().size();

		for (int i = 0; i < crystalNum; i++) {

			if (m_isDig) {
				m_isDig = false;
				return;
			}

			if (m_game->GetCrystalList()[i]->GetCrystalState() != m_game->GetCrystalList()[i]->m_enCrystalStete_Normal) {
				continue;
			}

			// ���W��擾
			Vector3 crystalPos = m_game->GetCrystalList()[i]->GetPosition();
			// ���g�̍��W����N���X�^���֌������x�N�g����쐬
			diff = crystalPos - m_position;

			// �Փ˂��Ă���Ȃ�
			if (!CrystalAndHit(m_position + (diff * ADD_LENGTH))) {
				// �~�`�Q�[�W��`�悷��
				m_pressAndHoldGauge->SetCanDrawGauge(true);
				// ���g�̍��W�������
				m_pressAndHoldGauge->Set3DPosition(m_position);
				// �N���X�^����ۑ�
				m_getCrystal = m_game->GetCrystalList()[i];
				m_crystalPosition = crystalPos;
				// �p�x�𑝂₷
				m_pressAndHoldGauge->SetChangeGaugeAngle(true);
				m_isDig = true;
				break;
			}

			// �~�`�Q�[�W��`�悷��
			m_pressAndHoldGauge->SetCanDrawGauge(false);
		}
	}
	else {
		// ���g�̍��W����N���X�^���֌������x�N�g����쐬
		diff = m_crystalPosition - m_position;

		// ���ȏ㗣�ꂽ��
		if (diff.Length() >= CAN_GET_LENGTH) {
			// �̌@���Ȃ�
			m_isDig = false;
			return;
		}

		// �Q�[�W���ő�łȂ��Ƃ��ȉ��̏����͎��s���Ȃ�
		if (m_pressAndHoldGauge->GetNowStatus() != m_pressAndHoldGauge->enGaugeState_Min) {
			return;
		}

		//m_game->GetCrystalList().erase(
		//	std::remove(m_game->GetCrystalList().begin(), m_game->GetCrystalList().end(),m_getCrystal),
		//	m_game->GetCrystalList().end()
		//);

		//while (it != m_game->GetCrystalList().end()) {
		//	if (*it == m_getCrystal) {
		//		it = m_game->GetCrystalList().erase(it);
		//	}
		//	else {
		//		it++;
		//	}
		//}

		// �l������
		m_getCrystal->SetCrystalState(m_crystal->m_enCrystalStete_HavePlayer);
		m_haveCrystals.push_back(m_getCrystal);

		m_sound->SetSoundSE(m_sound->m_enSoundState_GetSE);

		// �~�`�Q�[�W����Z�b�g����
		m_pressAndHoldGauge->ResetGaugeAngle();

		m_getCrystal = nullptr;
	}
}

void Player::IsClear()
{
	for (int i = 0; i < m_game->GetGoalList().size(); i++) {
		// �N���A���W�֌������x�N�g����쐬
		Vector3 diff = m_game->GetGoalList()[i] - m_position;
		
		if (diff.Length() <= CLEAR_LENGTH) {
			m_actionState = m_enActionState_Clear;
		}
	}
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}