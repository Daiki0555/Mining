#pragma once

namespace
{
	const int TEX_MAX = 4;
}

class Player;
class Crystal:public IGameObject
{
public:
	Crystal();
	~Crystal();

	bool Start();
	void Update();
	void GetCrystal();					// 自身を獲得する処理
	void Render(RenderContext& rc);

	/// <summary>
	/// 座標を設定する
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position) {
		m_position = position;
	}

	/// <summary>
	/// 座標を参照する
	/// </summary>
	/// <returns></returns>
	const Vector3 Getposition() const {
		return m_position;
	}

	/// <summary>
	/// スケールを設定する
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(const Vector3& scale) {
		m_scale = scale;
	}

	/// <summary>
	/// 回転を設定する
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotation(const Quaternion& rotation) {
		m_rotation = rotation;
	}

	/// <summary>
	/// モデルの設定
	/// </summary>
	void SetModel(/*int number*/) {
	}

private:

	/// <summary>
	/// レアリティを設定する
	/// </summary>
	/// <param name="rarity">自身のレア度</param>
	void SetRarity(const int& rarity) {
		m_myRarity = rarity;
	}


	ModelRender m_modelRender;						// モデルレンダー

	Vector3		m_position = Vector3::Zero;			// 座標
	Vector3		m_scale = Vector3::Zero;			// スケール
	Quaternion	m_rotation = Quaternion::Identity;	// 回転

	Texture		m_texture;							// テクスチャ

	int			m_myRarity = 0;						// 自身のレアリティ
};

