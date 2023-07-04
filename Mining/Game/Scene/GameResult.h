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
	/// �l����������ݒ肷��
	/// </summary>
	void SetScore(const int blueNum, const int pinkNum, const int yellowNum, const int greenNum) {
		m_newScore.m_crystalBlue = blueNum;
		m_newScore.m_crystalPink = pinkNum;
		m_newScore.m_crystalYellow = yellowNum;
		m_newScore.m_crystalGreen = greenNum;
	}

private:
	SpriteRender	m_spriteRender;			// �X�v���C�g�����_�[
	FontRender		m_fontRender;			// �t�H���g�����_�[

	struct Score {
		int			m_crystalBlue = 0;	
		int			m_crystalPink = 0;
		int			m_crystalYellow = 0;
		int			m_crystalGreen = 0;
		int			m_scoreSum = 0;			// �X�R�A�̑���
	};
	Score			m_newScore;				// �X�R�A
};

