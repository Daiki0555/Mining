#pragma once

class Player;

namespace
{
	const float STOP_TIME = 10.0f;		// �s�����~���鎞��
}

class EnemyBasic:public IGameObject
{
public:
	EnemyBasic();
	virtual ~EnemyBasic() = 0;

protected:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="attackPower">�U����</param>
	/// <param name="moveSpeed">��{�ړ����x</param>
	/// <param name="radius">�L�����N�^�[�R���g���[���[�̔��a</param>
	/// <param name="hight">�L�����N�^�[�R���g���[���[�̍���</param>
	/// <returns></returns>
	bool Start(int attackPower, float moveSpeed, float radius, float height);
	/// <summary>
	/// ��]����
	/// </summary>
	void Rotation(Vector3 rotaion);
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// �ҋ@���̏���
	/// </summary>
	void Idle();
	/// <summary>
	/// �U������
	/// </summary>
	void Attack();
	/// <summary>
	/// �s�����~����
	/// </summary>
	void StopAction();
	/// <summary>
	/// �ǂƂ̏Փ˔���
	/// </summary>
	/// <param name="targetPosition">�ړI�̍��W</param>
	/// <returns></returns>
	bool WallAndHit(Vector3 targetPosition);

public:
	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position) {
		m_position = position;
	}

	/// <summary>
	/// ���W���擾����
	/// </summary>
	/// <returns></returns>
	const Vector3 GetPosition() const {
		return m_position;
	}

	/// <summary>
	/// �X�P�[����ݒ�
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(const Vector3& scale) {
		m_scale = scale;
	}

	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotation(const Quaternion& rotation) {
		m_rotation = rotation;
	}

	/// <summary>
	/// �`�悷�邩�ǂ������肷��
	/// <param name="flag">true�Ȃ�`�悷��</param>
	void SetCanDrawFlag(bool flag) {
		m_canDraw = flag;
	}

	/// <summary>
	/// �`�悵�Ă��邩�ǂ������擾����
	/// </summary>
	bool GetCanDrawFlag() {
		return m_canDraw;
	}

	enum enActionState {
		m_enActionState_Idle,				// �ҋ@
		m_enActionState_Move,				// �ړ�
		m_enActionState_Attack,				// �U��
		m_enActionState_StopAction,			// �s����~
		m_enActionState_GameQuit			// �Q�[���I��
	};

	/// <summary>
	/// ���݂̃X�e�[�g���擾����
	/// </summary>
	/// <returns></returns>
	const enActionState GetEnemyStatus() const {
		return m_actionState;
	}

	/// <summary>
	/// �X�e�[�g��ݒ肷��
	/// </summary>
	/// <param name="state"></param>
	void SetEnemyState(const enActionState state) {
		m_actionState = state;
	}

protected:
	enActionState		m_actionState = m_enActionState_Idle;			// �s�����[�`��

	enum enAnimationClip {
		m_enAnimationClips_Idle,			// �ҋ@
		m_enAnimationClips_Move,			// �ړ�
		m_enAnimationClips_Attack,			// �U��
		m_enAnimationClips_Num
	};
	AnimationClip		m_enAnimationClips[m_enAnimationClips_Num];		// �A�j���[�V�����N���b�v

// -----------------------------------------------------------
	Player*				m_player = nullptr;								// �v���C���[

	CharacterController	m_characterController;							// �L�����N�^�[�R���g���[���[
	SphereCollider		m_sphereCollider;								// �X�t�B�A�R���C�_�[

	ModelRender			m_modelRender;									// ���f�������_�[

	Vector3				m_position = Vector3::Zero;						// ���g�̍��W
	Vector3				m_scale = Vector3::One;							// ���g�̃X�P�[��
	Quaternion			m_rotation = Quaternion::Identity;				// ���g�̉�]

	struct EnemyStatus {
		int				m_attackPower = 0;								// �U����
		float			m_basicSpeed = 0.0f;							// �ړ����x
	};

private:
	EnemyStatus			m_enemyStatus;									// �G�l�~�[�̃X�e�[�^�X

	float				m_StopTimer = STOP_TIME;						// �s�����~����^�C�}�[
	bool				m_canDraw = true;								// �`��ł��邩�ǂ���
};

