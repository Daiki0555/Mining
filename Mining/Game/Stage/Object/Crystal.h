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
	/// ���f���̐ݒ�
	/// </summary>
	void SetModel(/*int number*/) {
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

