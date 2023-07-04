#pragma once

class GameResult:public IGameObject
{
public:
	GameResult();
	~GameResult();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// 獲得した数を設定する
	/// </summary>
	void SetScore(const int blueNum, const int pinkNum, const int yellowNum, const int greenNum) {
		m_newScore.m_crystalBlue = blueNum;
		m_newScore.m_crystalPink = pinkNum;
		m_newScore.m_crystalYellow = yellowNum;
		m_newScore.m_crystalGreen = greenNum;
	}

private:
	SpriteRender	m_spriteRender;			// スプライトレンダー
	FontRender		m_fontRender;			// フォントレンダー

	struct Score {
		int			m_crystalBlue = 0;	
		int			m_crystalPink = 0;
		int			m_crystalYellow = 0;
		int			m_crystalGreen = 0;
		int			m_scoreSum = 0;			// スコアの総数
	};
	Score			m_newScore;				// スコア
};

