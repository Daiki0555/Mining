#include "stdafx.h"
#include "ScoreRanking.h"

#include"SaveDataManager.h"

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

	return true;
}

void ScoreRanking::Update()
{
}

void ScoreRanking:: Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}