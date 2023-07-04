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
	/// 新しいスコアを設定する
	/// </summary>
	/// <param name="score"></param>
	void SetNewScore(float score) {
		m_newScore = score;
	}

private:
	SpriteRender				m_spriteRender;			// スプライトレンダー
	SaveDataManager::SaveData	m_saveData;				// セーブデータの構造体

	int							m_newScore = 0;			// 新しいスコア
};

