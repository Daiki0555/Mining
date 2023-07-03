#pragma once
class Game;
class Title: public IGameObject
{
public:
	Title();
	~Title();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	/// <summary>
	/// ���ߏ���
	/// </summary>
	void Transparent();

private:
	ModelRender		m_modelRender;		// ���f�������_�[
	SpriteRender	m_spriteRender;		// �X�v���C�g�����_�[
	FontRender		m_fontRender;		// �t�H���g�����_�[

	Game*			m_game = nullptr;	// �Q�[��
};

