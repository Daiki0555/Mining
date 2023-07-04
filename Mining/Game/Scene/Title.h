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
	ModelRender		m_modelRender;			// モデルレンダー
	SpriteRender	m_spriteRenderTitle;	// スプライトレンダー(背景)
	SpriteRender	m_spriteRenderMessage;	// スプライトレンダー(文字)

	Game*			m_game = nullptr;		// ゲーム

	float			m_alpha = 1.0f;			// 透過値
};

