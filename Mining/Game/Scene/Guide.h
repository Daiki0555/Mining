#pragma once

class Title;
class Fade;

class Guide :public IGameObject
{
public:
	Guide();
	~Guide();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender	m_spriteRenderBackGround;							// �X�v���C�g�����_�[(�w�i)
	SpriteRender	m_spriteRenderGuide;								// �X�v���C�g�����_�[(�^�C�g��)
	SpriteRender	m_spriteRenderGuideImage;							// �X�v���C�g�����_�[(����摜)
	FontRender		m_fontRender;										// �t�H���g�����_�[
	Level2DRender*	m_level2DRender = nullptr;							// 2D�����_�[
	Fade*			m_fade = nullptr;									// �t�F�[�h
	bool			m_isWaitFadeOut = false;							// �t�F�[�h�A�E�g�̑ҋ@�����ǂ���
};

