#pragma once
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
	/// <param name="position"></param>
	void SetPosition(const Vector3& position) {
		m_position = position;
	}

	/// <summary>
	/// �X�P�[����ݒ肷��
	/// </summary>
	/// <param name="position"></param>
	void SetScale(const Vector3& scale) {
		m_scale = scale;
	}

	/// <summary>
	/// ��]��ݒ肷��
	/// </summary>
	/// <param name="position"></param>
	void SetRotation(const Quaternion& rotation) {
		m_rotation = rotation;
	}

private:
	enum ActionState {
		m_ActionState_Idle,			// �ҋ@
		m_ActionState_Walk,			// ����
		m_ActionState_Run,			// ����
		m_ActionState_Dig,			// �@��
		m_ActionState_Damage,		// ��e
		m_ActionState_Death,		// ���S
		m_ActionState_Clear			// �N���A
	};
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
	ModelRender			m_modelRender;						// ���f�������_�[

	CharacterController m_characterController;				// �L�����N�^�[�R���g���[���[

	Vector3				m_position = Vector3::Zero;			// ���g�̍��W
	Vector3				m_scale = Vector3::One;				// ���g�̃X�P�[��
	Vector3				m_moveSpeed = Vector3::Zero;		// �ړ����x

	Quaternion			m_rotation= Quaternion::Identity;	// ���g�̉�]

	struct PlayerStatus {
		int				m_hitPoint = 150;					// HP(150)
		int				m_attackPower = 25;					// �U����(25)
		float			m_stamina = 100.0f;					// �X�^�~�i(100.0f)
		float			m_basicSpeed = 100.0f;				// ��{���x(100.0f)
	};
	PlayerStatus		playerStatus;						// �v���C���[�̃X�e�[�^�X

	float				m_invincibleTimer = 5.0f;			// ���G����
	float				m_addSpped = 1.0f;					// ��Z���x

	bool				m_takeDamageflag = true;			// �_���[�W���󂯂�t���O
};

