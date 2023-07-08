#pragma once

#include"SaveDataManager.h"

class ScoreRanking : public IGameObject
{
public:
	ScoreRanking();
	~ScoreRanking();

	bool Start();
	void Render(RenderContext& rc);
	/// <summary>
	/// �����L���O��\������
	/// </summary>
	void DrawRanking();

	/// <summary>
	/// �V�����X�R�A��ݒ肷��
	/// </summary>
	/// <param name="score"></param>
	void SetNewScore(const float& score) {
		m_newScore = score;
	}

private:
	SpriteRender				m_spriteRender;			// �X�v���C�g�����_�[

	SaveDataManager				m_saveDataManager;
	SaveDataManager::SaveData	m_saveData;				// �Z�[�u�f�[�^�̍\����

	float						m_newScore = 0.0f;		// �V�����X�R�A
};

