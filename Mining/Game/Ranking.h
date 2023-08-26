#pragma once

class Fade;
class Sound;

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
	Level2DRender*	m_level2DRender = nullptr;		// 2D�����_�[
	SpriteRender	m_backGroundSpriteRender;		//�w�i�摜�B
	SpriteRender	m_rankingSpriteRender;			// �����L���O�摜
	SpriteRender	m_rankingScoresSpriteRender;	// �����L���O�̓���摜
	FontRender		m_rankingFontRender[10];		//�����L���O�����B
	FontRender		m_buttonFontRender;				//�{�^�������B
	Fade*			m_fade = nullptr;				//�t�F�[�h�N���X�B
	Sound*			m_sound = nullptr;				// �T�E���h�N���X
	bool			m_isWaitFadeOut = false;		//�t�F�[�h�A�E�g�̑ҋ@�����ǂ����B
};

