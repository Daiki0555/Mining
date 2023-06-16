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
	void GetCrystal();					// ���g���l�����鏈��
	void Render(RenderContext& rc);

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
	/// �e�N�X�`���̐ݒ�
	/// </summary>
	void SetTexture(/*int number*/) {

		int num = rand() % TEX_MAX;

		//// objct.number��0�̂Ƃ�
		//if (number == 0) {
		//	// �����_���ɐ���
		//	num = rand() % TEX_MAX;
		//}

		wchar_t path[255];
		wchar_t color[7];

		switch (num) {
		case 0:
			// �e�N�X�`����ݒ�
			wprintf_s(color, 7, L"Green");
			break;
		case 1:
			// �e�N�X�`����ݒ�
			wprintf_s(color, 7, L"Yellow");
			break;
		case 2:
			// �e�N�X�`����ݒ�
			wprintf_s(color, 7, L"Blue");
			break;
		case 3:
			// �e�N�X�`����ݒ�
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

		// ���A�x��ݒ�
		SetRarity(num);
	}

private:

	/// <summary>
	/// ���A���e�B��ݒ肷��
	/// </summary>
	/// <param name="rarity">���g�̃��A�x</param>
	void SetRarity(const int& rarity) {
		m_myRarity = rarity;
	}


	ModelRender m_modelRender;						// ���f�������_�[

	Vector3		m_position = Vector3::Zero;			// ���W
	Vector3		m_scale = Vector3::Zero;			// �X�P�[��
	Quaternion	m_rotation = Quaternion::Identity;	// ��]

	Texture		m_texture;							// �e�N�X�`��

	int			m_myRarity = 0;						// ���g�̃��A���e�B
};

