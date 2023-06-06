#pragma once
class EnemyBasic:public IGameObject
{
public:
	EnemyBasic();
	~EnemyBasic();

	bool Start();

	void Rotation();
	void Move();
	void SearchPlayer();
	void Attack();
	void Damege();
	void Dizzy();

	/// <summary>
	/// �X�e�[�^�X��ݒ肷��s
	/// </summary>
	/// <param name="attackPower">�U����</param>
	/// <param name="moveSpeed">�ړ����x</param>
	void SetStatus(float attackPower, float moveSpeed) {
		m_AttackPower = attackPower;
		m_MoveSpeed = moveSpeed;
	}

	/// <summary>
	/// �U���͂��Q�Ƃ���
	/// </summary>
	/// <returns></returns>
	float GetAttackPower() {
		return m_AttackPower;
	}

private:
	enum m_ActionState {
		m_ActionState_Idle,					// �ҋ@
		m_ActionState_Move,					// �ړ�
		m_ActionState_Attack,				// �U��
		m_ActionState_Damege,				// ��e
	};

	enum m_AnimationState {
		m_AnimationState_Idle,				// �ҋ@
		m_AnimationState_Move,				// �ړ�
		m_AnimationState_Attack,			// �U��
		m_AnimationState_Damege,			// ��e
	};

	enum EnAnimationClip {
		m_en_AnimationClips_Idle,				// �ҋ@
		m_en_AnimationClips_Move,				// �ړ�
		m_en_AnimationClips_Attack,				// �U��
		m_en_AnimationClips_Damege,				// ��e
		m_en_AnimationClips_Num
	};
	EnAnimationClip m_En_AnimationClips[m_en_AnimationClips_Num];

// -----------------------------------------------------------

	ModelRender		m_ModelRender;						// ���f�������_�[

	Vector3			m_Position = Vector3::Zero;			// ���g�̍��W
	Vector3			m_Scale = Vector3::Zero;			// ���g�̃X�P�[��
	Quaternion		m_Rotation = Quaternion::Identity;	// ���g�̉�]

	float			m_AttackPower = 0.0f;				// �U����
	float			m_MoveSpeed = 0.0f;					// �ړ����x
};

