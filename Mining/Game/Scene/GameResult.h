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
	SpriteRender	m_spriteRender;			// スプライトレンダー
	FontRender		m_fontRender;			// フォントレンダー

	Title*			m_title = nullptr;		// タイトル

	float			m_newScore = 0.0f;		// スコア
};

