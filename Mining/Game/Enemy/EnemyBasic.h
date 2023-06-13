#pragma once
class Player;
class EnemyBasic:public IGameObject
{
public:
	EnemyBasic();
	virtual ~EnemyBasic() = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="attackPower">�U����</param>
	/// <param name="moveSpeed">��{�ړ����x</param>
	/// <param name="radius">�L�����N�^�[�R���g���[���[�̔��a</param>
	/// <param name="hight">�L�����N�^�[�R���g���[���[�̍���</param>
	/// <returns></returns>
	bool Start(int attackPower, float moveSpeed, float radius, float height);

	void Rotation(Vector3 rotaion);
	void Move();
	void SearchPlayer();
	void Attack();
	void Damege();
	void Dizzy();

protected:
	enum ActionState {
		m_ActionState_Idle,					// �ҋ@
		m_ActionState_Move,					// �ړ�
		m_ActionState_Attack,				// �U��
		m_ActionState_Damage,				// ��e
	};
	ActionState m_actionState;

	enum EnAnimationClip {
		m_en_AnimationClips_Idle,			// �ҋ@
		m_en_AnimationClips_Move,			// �ړ�
		m_en_AnimationClips_Attack,			// �U��
		m_en_AnimationClips_Damage,			// ��e
		m_en_AnimationClips_Num
	};
	AnimationClip m_EnanimationClips[m_en_AnimationClips_Num];

// -----------------------------------------------------------
	Player*				m_player = nullptr;						// �v���C���[

	CharacterController	m_characterController;					// �L�����N�^�[�R���g���[���[

	ModelRender			m_modelRender;							// ���f�������_�[

	Vector3				m_position = Vector3::Zero;				// ���g�̍��W
	Vector3				m_scale = Vector3::One;					// ���g�̃X�P�[��
	Quaternion			m_rotation = Quaternion::Identity;		// ���g�̉�]

	struct EnemyStatus {
		int				m_attackPower = 0;						// �U����
		float			m_moveSpeed = 0.0f;						// �ړ����x
	};
	EnemyStatus			enemyStatus;							// �G�l�~�[�̃X�e�[�^�X
};
