#pragma once

class Title;
class Fade;

class Guide :public IGameObject
{
public:
	Guide();
	~Guide();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender	m_spriteRenderBackGround;							// スプライトレンダー(背景)
	SpriteRender	m_spriteRenderGuide;								// スプライトレンダー(タイトル)
	SpriteRender	m_spriteRenderGuideImage;							// スプライトレンダー(操作画像)
	FontRender		m_fontRender;										// フォントレンダー
	Level2DRender*	m_level2DRender = nullptr;							// 2Dレンダー
	Fade*			m_fade = nullptr;									// フェード
	bool			m_isWaitFadeOut = false;							// フェードアウトの待機中かどうか
};

