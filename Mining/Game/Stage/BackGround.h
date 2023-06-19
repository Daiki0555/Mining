#pragma once
class BackGround:public IGameObject
{
public:
	BackGround();
	~BackGround();

	bool Start();
	void Render(RenderContext& rc);

	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	void SetPosition (const Vector3& position) {
		m_position = position;
	}

	/// <summary>
	/// �X�P�[����ݒ�
	/// </summary>
	void SetScale(const Vector3& scale) {
		m_scale = scale;
	}

	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	void SetRotation(const Quaternion& rotaion) {
		m_rotaion = rotaion;
	}

private:
	ModelRender m_modelRender;						// ���f�������_�[

	PhysicsStaticObject m_physicsStaticObjct;		// �ÓI�����I�u�W�F�N�g

	Vector3		m_position = Vector3::Zero;			// ���W
	Vector3		m_scale = Vector3::One;				// �X�P�[��
	Quaternion	m_rotaion = Quaternion::Identity;	// ��]
};

