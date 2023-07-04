#include "stdafx.h"
#include "GameResult.h"

GameResult::GameResult()
{

}

GameResult::~GameResult()
{

}

bool GameResult::Start()
{
	return true;
}

void GameResult::Update()
{

}

void GameResult::Sort()
{
	for (int i = 0; i < m_rankingList.size(); i++) {

		if (m_newScore > m_ranking[i]) {

		}
		else if(m_newScore > m_ranking[i]) {

		}
		else if (m_newScore == m_ranking[i]) {

		}
	}
}

void GameResult::Render(RenderContext& rc)
{

}