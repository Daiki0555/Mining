#pragma once
class BackGround:public IGameObject
{
public:
	BackGround();
	~BackGround();

	bool Start();
	void Render(RenderContext& rc);

	/// <summary>
	/// 座標を設定
	/// </summary>
	void SetPosition (const Vector3& position) {
		m_position = position;
	}

	/// <summary>
	/// スケールを設定
	/// </summary>
	void SetScale(const Vector3& scale) {
		m_scale = scale;
	}

	/// <summary>
	/// 回転を設定
	/// </summary>
	void SetRotation(const Quaternion& rotaion) {
		m_rotaion = rotaion;
	}

private:
	ModelRender m_modelRender;						// モデルレンダー

	PhysicsStaticObject m_physicsStaticObjct;		// 静的物理オブジェクト

	Vector3		m_position = Vector3::Zero;			// 座標
	Vector3		m_scale = Vector3::One;				// スケール
	Quaternion	m_rotaion = Quaternion::Identity;	// 回転
};

