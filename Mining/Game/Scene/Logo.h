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
	SpriteRender	m_spriteRenderLogo;			// �X�v���C�g�����_�[(���S)
	SpriteRender	m_spriteRenderBackGround;	// �X�v���C�g�����_�[(�w�i�摜)
	FontRender		m_fontRender;				// �t�H���g�����_�[

	Level2DRender*	m_level2DRender = nullptr;	// 2D�����_�[
	Fade*			m_fade = nullptr;			// �t�F�[�h
	Title*			m_title = nullptr;			// �^�C�g��

	bool			m_isWaitFadeOut = false;	// �t�F�[�h�A�E�g�̑ҋ@�����ǂ���
	float			m_timer = 0.0f;				// �^�C�}�[
};

