#pragma once

#include"SaveDataManager.h"

class ScoreRanking : public IGameObject
{
public:
	ScoreRanking();
	~ScoreRanking();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// �V�����X�R�A��ݒ肷��
	/// </summary>
	/// <param name="score"></param>
	void SetNewScore(float score) {
		m_newScore = score;
	}

private:
	SpriteRender				m_spriteRender;			// �X�v���C�g�����_�[
	SaveDataManager::SaveData	m_saveData;				// �Z�[�u�f�[�^�̍\����

	int							m_newScore = 0;			// �V�����X�R�A
};

