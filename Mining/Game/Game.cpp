#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Stage/BackGround.h"

Game::Game()
{
}

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(m_backGround);
}

bool Game::Start()
{
	m_player = NewGO<Player>(0, "player");

	LevelDesign();

	return true;
}

void Game::LevelDesign()
{
	// レベルデザイン処理
	m_levelRender.Init("Assets/level/levelData.tkl", [&](LevelObjeData& objData){
		//名前がプレイヤーの時
		if (objData.EqualObjectName(L"box") == true)
		{
			m_backGround = NewGO<BackGround>(0, "backGround");
			m_backGround->SetPosition(objData.position);
			m_backGround->SetScale(objData.scale);
			m_backGround->SetRotation(objData.rotaition);
			return true;
		}

		return true;
		}
	);
}