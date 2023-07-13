#pragma once

class Game;
class Ranking;

class Title: public IGameObject
{
public:
	Title();
	~Title();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	/// <summary>
	/// �J�[�\���̈ړ�
	/// </summary>
	void ChangeCursor();
	/// <summary>
	/// �V�[���̑J��
	/// </summary>
	void ChangeScene();

private:
	enum enCursorState {
		m_enCursorState_Game,									// �Q�[��
		m_enCursorState_Guide,									// ����
		m_enCursorState_Ranking,								// �����L���O
	};
	enCursorState	m_enCursorState = m_enCursorState_Game;		// �I���ʒu�̃X�e�[�g

	ModelRender		m_modelRender;								// ���f�������_�[
	SpriteRender	m_spriteRenderTitle;						// �X�v���C�g�����_�[(�w�i)
	SpriteRender	m_spriteRenderMessage;						// �X�v���C�g�����_�[(����)

	Game*			m_game = nullptr;							// �Q�[��
	Ranking*		m_ranking = nullptr;						// �����L���O
	Fade*			m_fade = nullptr;							// �t�F�[�h

	float			m_alpha = 1.0f;								// ���ߒl
};

