#pragma once

class Title;

namespace
{
	const int CRYSTAL_CATEGORY_MAX = 4;			// �N���X�^���̎�ސ�
}

class GameResult:public IGameObject
{
public:
	GameResult();
	~GameResult();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	/// <summary>
	/// �X�R�A��\������
	/// </summary>
	void DrawScore();

	/// <summary>
	/// �N���X�^���̎擾����ݒ肷��
	/// </summary>
	/// <param name="num">�z��̔ԍ�</param>
	/// <param name="sum">��</param>
	void SetCrystalSum(const int num, const int sum) {
		m_haveCristals[num] = sum;
	}

private:
	SpriteRender							m_spriteRender;						// �X�v���C�g�����_�[
	FontRender								m_fontRender;						// �t�H���g�����_�[

	Title*									m_title = nullptr;					// �^�C�g��

	std::array<int, CRYSTAL_CATEGORY_MAX>	m_haveCristals = { 0,0,0,0 };		// player���擾�����N���X�^��
	int										m_newScore = 0;						// �X�R�A
};

