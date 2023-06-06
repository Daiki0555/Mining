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

	void Rotation(Vector3 rotation);
	void Move();
	void Attack();
	void Damage(float attackPower);
	void Dig();
	void Death();
	void Clear();

private:
	enum m_ActionState {
		m_ActionState_Idle,			// �ҋ@
		m_ActionState_Walk,			// ����
		m_ActionState_Run,			// ����
		m_ActionState_Dig,			// �@��
		m_ActionState_Damage,		// ��e
		m_ActionState_Death,		// ���S
		m_ActionState_Clear			// �N���A
	};

	enum m_AnimationState {
		m_AnimationState_Idle,		// �ҋ@
		m_AnimationState_Walk,		// ����
		m_AnimationState_Run,		// ����
		m_AnimationState_Dig,		// �@��
		m_AnimationState_Damage,	// ��e
		m_AnimationState_Death,		// ���S
		m_AnimationState_Clear		// �N���A
	};

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
	EnAnimationClip m_EnAnimationClips[m_en_AnimationClips_Num];

// --------------------------------------------------------
	ModelRender			m_ModelRender;						// ���f�������_�[

	CharacterController m_CharacterController;				// �L�����N�^�[�R���g���[���[

	Vector3				m_Position = Vector3::Zero;			// ���g�̍��W
	Vector3				m_Scale = Vector3::Zero;			// ���g�̃X�P�[��
	Quaternion			m_Rotation= Quaternion::Identity;	// ���g�̉�]

	float				m_HitPoint = 150.0f;				// HP
	float				m_Stamina = 100.0f;					// �X�^�~�i
	float				m_AttackPower = 50.0f;				// �U����
	float				m_MoveSpeed = 10.0f;				// �ړ����x
};

