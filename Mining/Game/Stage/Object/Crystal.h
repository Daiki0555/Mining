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
	/// テクスチャの設定
	/// </summary>
	void SetTexture(/*int number*/) {

		int num = rand() % TEX_MAX;

		//// objct.numberが0のとき
		//if (number == 0) {
		//	// ランダムに生成
		//	num = rand() % TEX_MAX;
		//}

		wchar_t path[255];
		wchar_t color[7];

		switch (num) {
		case 0:
			// テクスチャを設定
			wprintf_s(color, 7, L"Green");
			break;
		case 1:
			// テクスチャを設定
			wprintf_s(color, 7, L"Yellow");
			break;
		case 2:
			// テクスチャを設定
			wprintf_s(color, 7, L"Blue");
			break;
		case 3:
			// テクスチャを設定
			wprintf_s(color, 7, L"Pink");
			break;
		}

		wprintf_s(
			path,
			255,
			L"Asset/modelData/stage/Crystal/SmallCrystal_%lc.DDS",
			color
		);

		m_texture.InitFromDDSFile(path);

		// レア度を設定
		SetRarity(num);
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

