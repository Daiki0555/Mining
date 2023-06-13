#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Stage/BackGround.h"
#include "GameCamera.h"

Game::Game()
{
}

Game::~Game()
{
	Objct_DeleteGO();
}

void Game::Objct_DeleteGO()
{
	DeleteGO(m_player);
	DeleteGO(m_backGround);
	DeleteGO(m_gameCamera);
}

bool Game::Start()
{
	Objct_NewGO();
	LevelDesign();

	return true;
}

void Game::Objct_NewGO()
{
	m_player = NewGO<Player>(0, "player");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
}

void Game::LevelDesign()
{
	// レベルデザイン処理
	m_levelRender.Init("Assets/level/levelData.tkl", [&](LevelObjeData& objData){
		//名前がプレイヤーの時
		if (objData.EqualObjectName(L"stage") == true)
		{
			// 背景を描画
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