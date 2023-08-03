#pragma once
#include "physics/PhysicsGhostObject.h"

class PhysicsGhost:public IGameObject
{
public:
	PhysicsGhost();
	~PhysicsGhost();

	bool Start();

	/// <summary>
	/// ���W���擾����
	/// </summary>
	/// <returns></returns>
	const Vector3 GetPosition() const {
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

private:
	PhysicsGhostObject	m_physicsGhostObjct;				// �S�[�X�g

	Vector3				m_position = Vector3::Zero;			// ���W
	Vector3				m_scale = Vector3::Zero;			// �X�P�[��
	Quaternion			m_rotation = Quaternion::Identity;	// ��]
};

