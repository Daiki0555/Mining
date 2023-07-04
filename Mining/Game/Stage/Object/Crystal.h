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
	/// <summary>
	/// 自身を獲得する処理
	/// </summary>
	void GetCrystal();
	void Render(RenderContext& rc);

	// レアリティ
	enum EnCrystalRarity {
		EnCrystalRarity_Normal,
		EnCrystalRarity_HyperNormal,
		EnCrystalRarity_Rare,
		EnCrystalRarity_HyperRare,
	};

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
	const Vector3 GetPosition() const {
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

		SetRarity(num);
	}

	/// <summary>
	/// 描画フラグを設定する
	/// </summary>
	/// <param name="flag">trueなら描画する</param>
	void SetDrawFlag(const bool flag) {
		m_canDrawFlag = flag;
	}

	/// <summary>
	/// 描画フラグを取得する
	/// </summary>
	/// <returns></returns>
	bool GetDrawFlag() {
		return m_canDrawFlag;
	}

	/// <summary>
	/// レアリティを取得する
	/// </summary>
	/// <returns></returns>
	const int GetRarity()const {
		return m_crystalRarity;
	}

private:
	/// <summary>
	/// レアリティを設定する
	/// </summary>
	/// <param name="rarity">自身のレア度</param>
	void SetRarity(const int rarity) {

		int myRarity = EnCrystalRarity_Normal;

		switch (rarity) {
		case 1:
			myRarity = EnCrystalRarity_HyperNormal;
			break;
		case 2:
			myRarity = EnCrystalRarity_Rare;
			break;
		case 3:
			myRarity = EnCrystalRarity_HyperRare;
			break;
		}

		m_crystalRarity = myRarity;
	}

	PhysicsStaticObject m_physicsStaticObjct;

	ModelRender			m_modelRenderCrystal;				// モデルレンダー。クリスタル
	ModelRender			m_modelRenderRock;					// モデルレンダー。岩

	Vector3				m_position = Vector3::Zero;			// 座標
	Vector3				m_scale = Vector3::Zero;			// スケール
	Quaternion			m_rotation = Quaternion::Identity;	// 回転

	Texture				m_texture;							// テクスチャ

	int					m_crystalRarity;					// レアリティ

	bool				m_canDrawFlag = true;				// 描画できるかどうか
};

