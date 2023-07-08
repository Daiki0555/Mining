#include "stdafx.h"
#include "ScoreRanking.h"

#include"SaveDataManager.h"

namespace
{
	const int SCORE_ARRAYMAX = 11;		// 配列の最大値
}

ScoreRanking::ScoreRanking()
{
}

ScoreRanking::~ScoreRanking()
{

}

bool ScoreRanking::Start()
{
	m_spriteRender.Init("Assets/Sprite/UI/Scene/ranking.DDS", 1920.0f, 1080.0f);
	m_spriteRender.SetPosition({ 0.0f,0.0f,0.0f });
	m_spriteRender.Update();

	DrawRanking();

	return true;
}

void ScoreRanking::DrawRanking()
{
	// セーブデータをロード
	m_saveDataManager.Load(m_saveData);

	// 初期化
	for (int i = 0; i < SCORE_ARRAYMAX; i++) {
		if (m_saveData.score[i] != NULL) {
			break;
		}
		m_saveData.score[i] = 0.0f;
	}

	// 新しいスコアを代入する
	m_saveData.score[SCORE_ARRAYMAX - 1] = m_newScore;
	// ソート
	m_saveDataManager.Sort(m_saveData, m_newScore);

	// セーブ
	m_saveDataManager.Save(m_saveData);
}

void ScoreRanking:: Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}