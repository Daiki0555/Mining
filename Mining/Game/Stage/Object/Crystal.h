#pragma once

namespace
{
	const int TEX_MAX = 4;

	const wchar_t FILEPATH[TEX_MAX][255] = { L"Green",L"Yellow",L"Blue",L"Pink" };
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
	void SetTexture(/*int number*/) {

		int num = rand() % TEX_MAX;
		wchar_t path[255];
		const wchar_t* hoge = FILEPATH[num];

		//if (number == 0) {
		//	num = rand() % TEX_MAX;
		//}

		swprintf_s(
			path,
			255,
			L"Assets/modelData/stage/Crystal/SmallCrystal_%s.DDS",
			hoge
		);
		
		m_texture.InitFromDDSFile(path);
	}

private:

	/// <summary>
	/// レアリティを設定する
	/// </summary>
	/// <param name="rarity">自身のレア度</param>
	void SetRarity(const int& rarity) {
		m_myRarity = rarity;
	}


	ModelRender m_modelRenderCrystal;				// モデルレンダー。クリスタル
	ModelRender	m_modelRenderRock;					// モデルレンダー。岩

	Vector3		m_position = Vector3::Zero;			// 座標
	Vector3		m_scale = Vector3::Zero;			// スケール
	Quaternion	m_rotation = Quaternion::Identity;	// 回転

	Texture		m_texture;							// テクスチャ

	int			m_myRarity = 0;						// 自身のレアリティ
};

