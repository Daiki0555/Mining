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
	/// ランキングを表示する
	/// </summary>
	void DrawRanking();

	/// <summary>
	/// 新しいスコアを設定する
	/// </summary>
	/// <param name="score"></param>
	void SetNewScore(const float& score) {
		m_newScore = score;
	}

private:
	SpriteRender				m_spriteRender;			// スプライトレンダー

	SaveDataManager				m_saveDataManager;
	SaveDataManager::SaveData	m_saveData;				// セーブデータの構造体

	float						m_newScore = 0.0f;		// 新しいスコア
};

