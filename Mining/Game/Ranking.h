#pragma once


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
	SpriteRender	m_backGroundSpriteRender;		//背景画像。
	FontRender		m_rankingFontRender[10];		//ランキング文字。
	FontRender		m_buttonFontRender;				//ボタン文字。
};

