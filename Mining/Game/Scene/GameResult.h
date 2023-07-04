#pragma once

namespace
{
}

class GameResult:public IGameObject
{
	GameResult();
	~GameResult();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	/// <summary>
	/// ソート
	/// </summary>
	void Sort();

	/// <summary>
	/// 新しいスコアを設定する
	/// </summary>
	/// <param name="score"></param>
	void SetNewScore(float score) {
		m_newScore = score;
	}

private:
	SpriteRender			m_spriteRender;
	FontRender				m_fontRender;

	struct ScoreBord {
		int					m_score = 0;			// スコア
	};

	int						m_newScore = 0;			// 新しいスコア
	std::vector<ScoreBord>	m_rankingList;			// ランキング
};

