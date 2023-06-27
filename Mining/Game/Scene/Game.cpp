#include "stdafx.h"
#include "Game.h"
#include "GameClear.h"
#include "GameOver.h"
#include "Player.h"
#include "Stage/BackGround.h"
#include "GameCamera.h"
#include "Enemy/Enemy_Bee.h"
#include "Enemy/Enemy_Mushroom.h"
#include "Enemy/Enemy_Slime.h"
#include "Stage/Object/Crystal.h"
#include "UI/PlayerStatusGauge.h"
#include "UI/PressAndHoldGauge.h"

Game::Game()
{
}

Game::~Game()
{
	m_crystalList.clear();

	Objct_DeleteGO();
}

void Game::Objct_DeleteGO()
{
	DeleteGO(m_player);
	DeleteGO(m_backGround);
	DeleteGO(m_gameCamera);

	//for (int i = 0; i < m_crystalList.size(); i++) {
	//	DeleteGO(m_crystalList[i]);
	//}
}

bool Game::Start()
{
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_circleGauge = NewGO<PressAndHoldGauge>(0, "pressAndHoldGauge");

	LevelDesign();

	m_playerStatusGauge = NewGO<PlayerStatusGauge>(0, "playerStatusGauge");

	return true;
}

void Game::LevelDesign()
{
	// レベルデザイン処理
	m_levelRender.Init("Assets/level/levelData.tkl", [&](LevelObjeData& objData){
		//名前がstageの時
		if (objData.EqualObjectName(L"stage") == true)
		{
			// 背景を描画
			m_backGround = NewGO<BackGround>(0, "backGround");
			m_backGround->SetPosition(objData.position);
			m_backGround->SetScale(objData.scale);
			m_backGround->SetRotation(objData.rotaition);
			return true;
		}
		// 名前がghostのとき
		if (objData.EqualObjectName(L"ghost") == true)
		{
			
		}
		// 名前がcrystalのとき
		if (objData.EqualObjectName(L"crystal") == true) 
		{
			Crystal* m_crystal = NewGO<Crystal>(0, "crystal");
			m_crystal->SetPosition(objData.position);
			m_crystal->SetScale(objData.scale);
			m_crystal->SetRotation(objData.rotaition);
			m_crystal->SetTexture();

			// 総数を追加
			m_crystalList.push_back(m_crystal);
			return true;
		}
		//名前がplayerの時
		if (objData.EqualObjectName(L"player") == true)
		{
			// プレイヤーを生成
			m_player = NewGO<Player>(0, "player");
			m_player->SetPosition(objData.position);
			m_player->SetRotation(objData.rotaition);
			return true;
		}
		// 名前がenemyのとき
		if (objData.EqualObjectName(L"enemy") == true)
		{
			//Enemy_Bee* m_bee = NewGO<Enemy_Bee>(0, "bee");
			//m_bee->SetPosition(objData.position);
			//m_bee->SetRotation(objData.rotaition);

			//Enemy_Slime* m_slime = NewGO<Enemy_Slime>(0, "slime");
			//m_slime->SetPosition(objData.position);
			//m_slime->SetRotation(objData.rotaition);

			//Enemy_Mushroom* m_mushroom = NewGO<Enemy_Mushroom>(0, "mushroom");
			//m_mushroom->SetPosition(objData.position);
			//m_mushroom->SetRotation(objData.rotaition);
			return true;
		}

		return true;
		}
	);
}

void Game::Update()
{
	if (m_player->GetHitPoint() <= 0) {
		m_enGameState = m_enGameState_GameOver;
	}
}