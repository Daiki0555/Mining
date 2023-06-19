#pragma once
class Enemy_Slime;
class Enemy_Mushroom;
class Enemy_Bee;
class Crystal;

namespace 
{
	const int	HIT_POINT = 150;			// HP
	const int	ATTACK_POWER = 25;			// �U����
	const float	STAMINA = 100.0f;			// �X�^�~�i
	const float BASIC_SPEED = 150.0f;		// �ړ����x

	const float INVINCIBLE_TIMER = 5.0f;	// ���G����
}

class Player :public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void LoadAnimation();
	void PlayAnimation();

	void Rotation();
	void Move();
	void Attack();
	void Damage(int attackPower);
	void Dig();
	void Death();
	void Clear();

	void HitCrstal();

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
	const int GetCrystalSum() const {
		return m_haveCrystals.size();
	}

	enum ActionState {
		m_ActionState_Idle,			// �ҋ@
		m_ActionState_Walk,			// ����
		m_ActionState_Run,			// ����
		m_ActionState_Dig,			// �@��
		m_ActionState_Damage,		// ��e
		m_ActionState_Death,		// ���S
		m_ActionState_Clear			// �N���A
	};

	/// <summary>
	/// ���݂̃X�e�[�g��Ԃ�
	/// </summary>
	const ActionState GetActionState() const {
		return m_actionState;
	}

private:
	/// <summary>
	/// �N���X�^���̐���ǉ�
	/// </summary>
	/// <param name="num">���A�x</param>
	/// <returns></returns>
	void AddCrystalNum(const int& num){
		m_haveCrystals.push_back(num);
	}

	ActionState m_actionState;

	enum EnAnimationClip {
		m_en_AnimationClips_Idle,		// �ҋ@
		m_en_AnimationClips_Walk,		// ����
		m_en_AnimationClips_Run,		// ����
		m_en_AnimationClips_Dig,		// �@��
		m_en_AnimationClips_Damage,		// ��e
		m_en_AnimationClips_Death,		// ���S
		m_en_AnimationClips_Clear,		// �N���A
		m_en_AnimationClips_Num
	};
	AnimationClip m_EnAnimationClips[m_en_AnimationClips_Num];

// --------------------------------------------------------
	ModelRender			m_modelRender;							// ���f�������_�[

	CharacterController m_characterController;					// �L�����N�^�[�R���g���[���[

	Vector3				m_position = Vector3::Zero;				// ���g�̍��W
	Vector3				m_scale = Vector3::One;					// ���g�̃X�P�[��
	Vector3				m_moveSpeed = Vector3::Zero;			// �ړ����x

	Quaternion			m_rotation= Quaternion::Identity;		// ���g�̉�]

	Crystal*			m_crystal = nullptr;					// �N���X�^��

	struct PlayerStatus {
		int				m_hitPoint = HIT_POINT;					// HP
		int				m_attackPower = ATTACK_POWER;			// �U����
		float			m_stamina = STAMINA;					// �X�^�~�i
		float			m_basicSpeed = BASIC_SPEED;				// ��{���x
	};
	PlayerStatus		m_playerStatus;							// �v���C���[�̃X�e�[�^�X

	float				m_invincibleTimer = INVINCIBLE_TIMER;	// ���G����
	float				m_addSpped = 0.0f;						// ��Z���x

	bool				m_canDamageflag = true;					// �_���[�W���󂯂��邩�ǂ���

	std::list<int>	m_haveCrystals;								// �������Ă���N���X�^��
};

