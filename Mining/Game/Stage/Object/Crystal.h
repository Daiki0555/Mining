#pragma once

namespace
{
	const int TEX_MAX = 100;

	const wchar_t FILEPATH[TEX_MAX][255] = { L"Green",L"Yellow",L"Blue",L"Pink" };
}

class Player;
class Crystal:public IGameObject
{
public:
	Crystal();
	~Crystal();

	bool Start();
	void Render(RenderContext& rc);

	// レアリティ
	enum enCrystalRarity {
		m_enCrystalRarity_NormalRare,
		m_enCrystalRarity_SuperRare,
		m_enCrystalRarity_HyperRare,
		m_enCrystalRarity_MysticRare,
	};

	enum enCrystalState {
		m_enCrystalStete_Normal,		// 標準
		m_enCrystalStete_HavePlayer,	// プレイヤーが獲得した
		m_enCrystalState_NotDraw		// 描画しない(描画範囲外)
	};

	/// <summary>
	/// ステートを設定する
	/// </summary>
	void SetCrystalState(enCrystalState state) {
		m_crystalState = state;
	}

	/// <summary>
	/// ステートを参照する
	/// </summary>
	/// <returns></returns>
	const enCrystalState GetCrystalState()const {
		return m_crystalState;
	}

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
	void SetTexture() {

		int num = rand() % TEX_MAX;
		int pathNum = 0;
		wchar_t path[255];

		// 番号を設定
		if (num >= 0 && num <= 10) {
			pathNum = m_enCrystalRarity_HyperRare;
		}
		else if (num > 10 && num <= 35) {
			pathNum = m_enCrystalRarity_MysticRare;
		}
		else if (num > 35 && num <= 65) {
			pathNum = m_enCrystalRarity_SuperRare;
		}
		else {
			pathNum = m_enCrystalRarity_NormalRare;
		}

		const wchar_t* hoge = FILEPATH[pathNum];

		// テクスチャを再設定
		swprintf_s(
			path,
			255,
			L"Assets/modelData/stage/Crystal/SmallCrystal_%s.DDS",
			hoge
		);
		
		m_texture.InitFromDDSFile(path);

		SetRarity(pathNum);
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

		int myRarity = m_enCrystalRarity_NormalRare;

		switch (rarity) {
		case 1:
			myRarity = m_enCrystalRarity_SuperRare;
			break;
		case 2:
			myRarity = m_enCrystalRarity_MysticRare;
			break;
		case 3:
			myRarity = m_enCrystalRarity_HyperRare;
			break;
		}

		m_crystalRarity = myRarity;
	}

	PhysicsStaticObject m_physicsStaticObjct;

	ModelRender			m_modelRenderCrystal;						// モデルレンダー。クリスタル
	ModelRender			m_modelRenderRock;							// モデルレンダー。岩

	Vector3				m_position = Vector3::Zero;					// 座標
	Vector3				m_scale = Vector3::Zero;					// スケール
	Quaternion			m_rotation = Quaternion::Identity;			// 回転

	Texture				m_texture;									// テクスチャ

	enCrystalState		m_crystalState = m_enCrystalStete_Normal;	// ステート

	int					m_crystalRarity;							// レアリティ
};

