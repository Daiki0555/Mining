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
	/// �\�[�g
	/// </summary>
	void Sort();

	/// <summary>
	/// �V�����X�R�A��ݒ肷��
	/// </summary>
	/// <param name="score"></param>
	void SetNewScore(float score) {
		m_newScore = score;
	}

private:
	SpriteRender			m_spriteRender;
	FontRender				m_fontRender;

	struct ScoreBord {
		int					m_score = 0;			// �X�R�A
	};

	int						m_newScore = 0;			// �V�����X�R�A
	std::vector<ScoreBord>	m_rankingList;			// �����L���O
};

