#pragma once

class Game;
class ScoreRanking;

class Title: public IGameObject
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
	void Transparent();
	/// <summary>
	/// �V�[���̑J��
	/// </summary>
	void SceneChange();

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
	ScoreRanking*	m_scoreRanking = nullptr;					// �����L���O

	float			m_alpha = 1.0f;								// ���ߒl
};

