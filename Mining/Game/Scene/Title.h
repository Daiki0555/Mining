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
	ModelRender		m_modelRender;			// ���f�������_�[
	SpriteRender	m_spriteRenderTitle;	// �X�v���C�g�����_�[(�w�i)
	SpriteRender	m_spriteRenderMessage;	// �X�v���C�g�����_�[(����)

	Game*			m_game = nullptr;		// �Q�[��

	float			m_alpha = 1.0f;			// ���ߒl
};

