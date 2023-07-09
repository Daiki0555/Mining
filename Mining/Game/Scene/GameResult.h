#pragma once

class Title;

class GameResult:public IGameObject
{
public:
	GameResult();
	~GameResult();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender	m_spriteRender;			// �X�v���C�g�����_�[
	FontRender		m_fontRender;			// �t�H���g�����_�[

	Title*			m_title = nullptr;		// �^�C�g��

	float			m_newScore = 0.0f;		// �X�R�A
};

