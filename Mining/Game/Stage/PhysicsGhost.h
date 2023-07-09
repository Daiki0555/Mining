#pragma once
#include "physics/PhysicsGhostObject.h"

class PhysicsGhost:public IGameObject
{
public:
	PhysicsGhost();
	~PhysicsGhost();

	bool Start();

	/// <summary>
	/// 座標を取得する
	/// </summary>
	/// <returns></returns>
	const Vector3 GetPosition() const {
		return m_position;
	}

	/// <summary>
	/// 座標を設定する
	/// </summary>
	void SetPosition(const Vector3& position) {
		m_position = position;
	}

	/// <summary>
	/// スケールを設定する
	/// </summary>
	void SetScale(const Vector3& scale) {
		m_scale = scale;
	}

	/// <summary>
	/// 回転を設定する
	/// </summary>
	void SetRotation(const Quaternion& rotation) {
		m_rotation = rotation;
	}

private:
	PhysicsGhostObject	m_physicsGhostObjct;				// ゴースト

	Vector3				m_position = Vector3::Zero;			// 座標
	Vector3				m_scale = Vector3::Zero;			// スケール
	Quaternion			m_rotation = Quaternion::Identity;	// 回転
};

