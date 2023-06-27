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
	void GetCrystal();					// ���g���l�����鏈��
	void Render(RenderContext& rc);

	// ���A���e�B
	enum EnCrystalRarity {
		EnCrystalRarity_Normal,			// 10
		EnCrystalRarity_HyperNormal,	// 15
		EnCrystalRarity_Rare,			// 20
		EnCrystalRarity_HyperRare,		// 25
	};

	/// <summary>
	/// ���W��ݒ肷��
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position) {
		m_position = position;
	}

	/// <summary>
	/// ���W���Q�Ƃ���
	/// </summary>
	/// <returns></returns>
	const Vector3 Getposition() const {
		return m_position;
	}

	/// <summary>
	/// �X�P�[����ݒ肷��
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(const Vector3& scale) {
		m_scale = scale;
	}

	/// <summary>
	/// ��]��ݒ肷��
	/// </summary>
	/// <param name="rotation"></param>
	void SetRotation(const Quaternion& rotation) {
		m_rotation = rotation;
	}

	/// <summary>
	/// ���f���̐ݒ�
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
	/// ���A���e�B���擾����
	/// </summary>
	/// <returns></returns>
	const EnCrystalRarity GetRarity()const {
		return m_crystalRarity;
	}

private:
	/// <summary>
	/// ���A���e�B��ݒ肷��
	/// </summary>
	/// <param name="rarity">���g�̃��A�x</param>
	void SetRarity(const int rarity) {

		EnCrystalRarity myRarity;

		switch (rarity) {
		case 0:
			myRarity = EnCrystalRarity_Normal;
			break;
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

	ModelRender			m_modelRenderCrystal;				// ���f�������_�[�B�N���X�^��
	ModelRender			m_modelRenderRock;					// ���f�������_�[�B��

	Vector3				m_position = Vector3::Zero;			// ���W
	Vector3				m_scale = Vector3::Zero;			// �X�P�[��
	Quaternion			m_rotation = Quaternion::Identity;	// ��]

	Texture				m_texture;							// �e�N�X�`��

	EnCrystalRarity		m_crystalRarity;					// ���A���e�B

	bool				m_canDrawFlag = true;				// �`��ł��邩�ǂ���
};

