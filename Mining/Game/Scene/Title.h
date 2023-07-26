#pragma once

class Game;
class Ranking;
class Fade;
class Guide;

class Title : public IGameObject
{
public:
	Title();
	~Title();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	/// <summary>
	/// ���ߏ���
	/// </summary>
	void TransparentProcess();
	/// <summary>
	/// �V�[���̑J��
	/// </summary>
	void ChangeScene();
	/// <summary>
	/// �V�[���̐؂�ւ�
	/// </summary>
	void FadeScene();
	/// <summary>
	/// UV�X�N���[���̏���
	/// </summary>
	void UVScroll();

private:
	enum enMessageState {
		m_enMessageState_Start,											// �X�^�[�g
		m_enMessageState_Select											// �Z���N�g
	};
	enMessageState	m_MessageState = m_enMessageState_Start;			// �\�����Ă��郁�b�Z�[�W

	enum enCursorState {
		m_enCursorState_Game,											// �Q�[��
		m_enCursorState_Guide,											// ����
		m_enCursorState_Ranking,										// �����L���O
	};
	enCursorState	m_CursorState = m_enCursorState_Game;				// �I���ʒu�̃X�e�[�g

	SpriteRender	m_spriteRenderTitle;								// �X�v���C�g�����_�[(�w�i)
	SpriteRender	m_spriteRenderRogo;									// �X�v���C�g�����_�[(���S)
	SpriteRender	m_spriteRenderIcon;									// �X�v���C�g�����_�[(�A�C�R��)
	SpriteRender	m_spriteRenderUV;									// UV�X�N���[���摜

	FontRender		m_StartMessage;										// �J�n�̕���
	FontRender		m_GameStartMessage;									// �Q�[���J�n�̕���
	FontRender		m_RankingMessage;									// �����L���O�\���̕���
	FontRender		m_SystemMessage;									// �V�X�e���̕���

	Level2DRender*	m_level2DRender = nullptr;							// 2D�����_�[
	Game*			m_game = nullptr;									// �Q�[��
	Ranking*		m_ranking = nullptr;								// �����L���O
	Fade*			m_fade = nullptr;									// �t�F�[�h
	Guide*			m_guide = nullptr;									// �������

	float			m_alpha = 1.0f;										// �����x
	bool			m_isChange = false;									// ���߂̐؂�ւ�
	bool			m_isWaitFadeOut = false;							// �t�F�[�h�A�E�g�̑ҋ@�����ǂ���
};