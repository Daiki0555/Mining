#pragma once

class Fade;
class Title;

/// <summary>
/// ランキングクラス。
/// </summary>
class Ranking : public IGameObject
{
public:
	Ranking();
	~Ranking();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	/// <summary>
	/// ランキングの初期化。
	/// </summary>
	void InitRanking();

private:
	Level2DRender*	m_level2DRender = nullptr;		// 2Dレンダー
	SpriteRender	m_backGroundSpriteRender;		//背景画像。
	SpriteRender	m_rankingSpriteRender;			// ランキング画像
	SpriteRender	m_rankingScoresSpriteRender;	// ランキングの内訳画像
	FontRender		m_rankingFontRender[10];		//ランキング文字。
	FontRender		m_buttonFontRender;				//ボタン文字。
	Title*			m_title = nullptr;				//タイトルクラス。
	Fade*			m_fade = nullptr;				//フェードクラス。
	bool			m_isWaitFadeOut = false;		//フェードアウトの待機中かどうか。
};

