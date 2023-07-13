#pragma once
class Game;
class Crystal;
class PressAndHoldGauge;

namespace 
{
	const int	HIT_POINT = 150;			// HP
	const int	ATTACK_POWER = 25;			// �U����
	const float	STAMINA = 100.0f;			// �X�^�~�i
	const float BASIC_SPEED = 150.0f;		// �ړ����x

	const float INVINCIBLE_TIMER = 5.0f;	// ���G����
	const float RECOVERY_TIMER = 2.0f;		// �X�^�~�i���񕜂���܂ł̎���

	const float ADDSPEED = 0.5f;			// �_�b�V�����̉��Z���x
}

class Player :public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// �A�j���[�V�����̃��[�h
	/// </summary>
	void LoadAnimation();
	/// <summary>
	/// �A�j���[�V�����̍Đ�
	/// </summary>
	void PlayAnimation();
	/// <summary>
	/// ��]����
	/// </summary>
	void Rotation();
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// ��e����
	/// </summary>
	/// <param name="attackPower">����̍U����</param>
	void Damage(int attackPower);
	/// <summary>
	/// �̌@����
	/// </summary>
	void Dig();
	/// <summary>
	/// ���S����
	/// </summary>
	void Death();
	/// <summary>
	/// �N���A���Ă��邩�ǂ����𔻒�
	/// </summary>
	void IsClear();
	/// <summary>
	/// �N���A����
	/// </summary>
	void Clear();
	/// <summary>
	/// �N���X�^���Ƃ̏Փ˔���
	/// </summary>
	/// <param name="targetPosition">�ړI�̍��W</param>
	/// <returns></returns>
	bool CrystalAndHit(Vector3 targetPosition);

	/// <summary>
	/// ���W���Q�Ƃ���
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition()const {
		return m_position;
	}

	/// <summary>
	/// ���W��ݒ肷��
	/// </summary>
	void SetPosition(const Vector3& position) {
		m_position = position;
	}

	/// <summary>
	/// �X�P�[����ݒ肷��
	/// </summary>
	void SetScale(const Vector3& scale) {
		m_scale = scale;
	}

	/// <summary>
	/// ��]��ݒ肷��
	/// </summary>
	void SetRotation(const Quaternion& rotation) {
		m_rotation = rotation;
	}

	/// <summary>
	/// �N���X�^���̑������擾
	/// </summary>
	inline std::vector<Crystal*> GetCrystalList() const {
		return m_haveCrystals;
	}

	enum enActionState {
		m_enActionState_Idle,			// �ҋ@
		m_enActionState_Walk,			// ����
		m_enActionState_Run,			// ����
		m_enActionState_Dig,			// �@��
		m_enActionState_Damage,			// ��e
		m_enActionState_Death,			// ���S
		m_enActionState_Clear			// �N���A
	};

	/// <summary>
	/// �X�e�[�g��ݒ肷��
	/// </summary>
	/// <param name="state"></param>
	void SetActionState(enActionState state) {
		m_actionState = state;
	}

	/// <summary>
	/// ���݂̃X�e�[�g��Ԃ�
	/// </summary>
	const enActionState GetActionState() const {
		return m_actionState;
	}

	/// <summary>
	/// �v���C���[��HP���Q�Ƃ���
	/// </summary>
	/// <returns></returns>
	const int GetHitPoint() const {
		return m_playerStatus.m_hitPoint;
	}

	/// <summary>
	/// �v���C���[�̃X�^�~�i���Q�Ƃ���
	/// </summary>
	/// <returns></returns>
	const int GetStamina() const {
		return m_playerStatus.m_stamina;
	}

	/// <summary>
	/// �_���[�W���󂯂��邩�ǂ����̃t���O���Q�Ƃ���
	/// </summary>
	/// <returns></returns>
	const bool GetCanDamege() const {
		return m_canAddDamage;
	}

private:
	enActionState			m_actionState = m_enActionState_Idle;

	enum enAnimationClip {
		m_en_AnimationClips_Idle,		// �ҋ@
		m_en_AnimationClips_Walk,		// ����
		m_en_AnimationClips_Run,		// ����
		m_en_AnimationClips_Dig,		// �@��
		m_en_AnimationClips_Damage,		// ��e
		m_en_AnimationClips_Death,		// ���S
		m_en_AnimationClips_Clear,		// �N���A
		m_en_AnimationClips_Num
	};
	AnimationClip			m_enAnimationClips[m_en_AnimationClips_Num];

// --------------------------------------------------------
	ModelRender				m_modelRender;									// ���f�������_�[

	CharacterController		m_characterController;							// �L�����N�^�[�R���g���[���[
	SphereCollider			m_sphereCollider;								// �X�t�B�A�R���C�_�[


	Vector3					m_position = Vector3::Zero;						// ���g�̍��W
	Vector3					m_scale = Vector3::One;							// ���g�̃X�P�[��
	Vector3					m_basicSpeed = Vector3::Zero;					// �ړ����x
	Vector3					m_crystalPosition = Vector3::Zero;				// �l������N���X�^���̍��W

	Quaternion				m_rotation= Quaternion::Identity;				// ���g�̉�]

	Game*					m_game = nullptr;								// �Q�[��
	Crystal*				m_crystal = nullptr;							// �N���X�^��
	Crystal*				m_getCrystal = nullptr;							// �l�������N���X�^��
	PressAndHoldGauge*		m_pressAndHoldGauge = nullptr;					// �~�`�Q�[�W

	std::vector<Crystal*>	m_haveCrystals;									// �������Ă���N���X�^��

	struct PlayerStatus {
		int					m_hitPoint = HIT_POINT;							// HP
		int					m_attackPower = ATTACK_POWER;					// �U����
		float				m_stamina = STAMINA;							// �X�^�~�i
		float				m_basicSpeed = BASIC_SPEED;						// ��{���x
	};
	PlayerStatus			m_playerStatus;									// �v���C���[�̃X�e�[�^�X

	float					m_recoveryTimer = RECOVERY_TIMER;				// �X�^�~�i���񕜂��n�߂�܂ł̎���
	float					m_invincibleTimer = INVINCIBLE_TIMER;			// ���G����
	float					m_addSpped = 0.0f;								// ��Z����ړ����x
	float					m_addValue = ADDSPEED;							// �ړ����x�Ɣ�r���邽�߂̕ϐ�

	bool					m_canAddDamage = true;							// �_���[�W���󂯂��邩�ǂ���
	bool					m_isDig = false;								// �̌@���Ă��邩�ǂ���
};

