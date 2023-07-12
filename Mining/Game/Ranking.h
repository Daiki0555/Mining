#pragma once


/// <summary>
/// �����L���O�N���X�B
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
	/// �����L���O�̏������B
	/// </summary>
	void InitRanking();

private:
	SpriteRender	m_backGroundSpriteRender;		//�w�i�摜�B
	FontRender		m_rankingFontRender[10];		//�����L���O�����B
	FontRender		m_buttonFontRender;				//�{�^�������B
};

