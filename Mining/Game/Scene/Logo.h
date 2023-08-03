#pragma once

class Fade;
class Title;

class Logo : public IGameObject
{
public:
	Logo();
	~Logo();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender	m_spriteRenderLogo;			// スプライトレンダー(ロゴ)
	SpriteRender	m_spriteRenderBackGround;	// スプライトレンダー(背景画像)
	FontRender		m_fontRender;				// フォントレンダー

	Level2DRender*	m_level2DRender = nullptr;	// 2Dレンダー
	Fade*			m_fade = nullptr;			// フェード
	Title*			m_title = nullptr;			// タイトル

	bool			m_isWaitFadeOut = false;	// フェードアウトの待機中かどうか
	float			m_timer = 0.0f;				// タイマー
};

