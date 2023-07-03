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
	/// 透過処理
	/// </summary>
	void Transparent();

private:
	ModelRender		m_modelRender;		// モデルレンダー
	SpriteRender	m_spriteRender;		// スプライトレンダー
	FontRender		m_fontRender;		// フォントレンダー

	Game*			m_game = nullptr;	// ゲーム
};

