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

	// ���A���e�B
	enum enCrystalRarity {
		m_enCrystalRarity_NormalRare,
		m_enCrystalRarity_SuperRare,
		m_enCrystalRarity_HyperRare,
		m_enCrystalRarity_MysticRare,
	};

	enum enCrystalState {
		m_enCrystalStete_Normal,		// �W��
		m_enCrystalStete_HavePlayer,	// �v���C���[���l������
		m_enCrystalState_NotDraw		// �`�悵�Ȃ�(�`��͈͊O)
	};

	/// <summary>
	/// �X�e�[�g��ݒ肷��
	/// </summary>
	void SetCrystalState(enCrystalState state) {
		m_crystalState = state;
	}

	/// <summary>
	/// �X�e�[�g���Q�Ƃ���
	/// </summary>
	/// <returns></returns>
	const enCrystalState GetCrystalState()const {
		return m_crystalState;
	}

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
	const Vector3 GetPosition() const {
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
	void SetTexture() {

		int num = rand() % TEX_MAX;
		int pathNum = 0;
		wchar_t path[255];

		// �ԍ���ݒ�
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

		// �e�N�X�`�����Đݒ�
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
	/// ���A���e�B���擾����
	/// </summary>
	/// <returns></returns>
	const int GetRarity()const {
		return m_crystalRarity;
	}

private:
	/// <summary>
	/// ���A���e�B��ݒ肷��
	/// </summary>
	/// <param name="rarity">���g�̃��A�x</param>
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

	ModelRender			m_modelRenderCrystal;						// ���f�������_�[�B�N���X�^��
	ModelRender			m_modelRenderRock;							// ���f�������_�[�B��

	Vector3				m_position = Vector3::Zero;					// ���W
	Vector3				m_scale = Vector3::Zero;					// �X�P�[��
	Quaternion			m_rotation = Quaternion::Identity;			// ��]

	Texture				m_texture;									// �e�N�X�`��

	enCrystalState		m_crystalState = m_enCrystalStete_Normal;	// �X�e�[�g

	int					m_crystalRarity;							// ���A���e�B
};

