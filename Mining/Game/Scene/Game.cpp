#include "stdafx.h"
#include "Game.h"

#include "GameCamera.h"
#include "Player.h"
#include "Stage/BackGround.h"
#include "Stage/PhysicsGhost.h"
#include "Stage/Object/Crystal.h"
#include "Enemy/Enemy_Stone.h"
#include "Enemy/Enemy_Mushroom.h"
#include "Enemy/Enemy_Slime.h"
#include "UI/PlayerStatusGauge.h"
#include "UI/PressAndHoldGauge.h"
#include "UI/Fade.h"
#include "Scene/GameResult.h"

namespace
{
	const Vector3	LIGHT_COLOR = { 10.0f,10.0f,10.0f };		// ライトのカラー
	const float		Y_UP = 0.0f;								// ライトを持ち上げる値

	const float		CANDRAW_LENGTH = 3500.0f;					// 描画できる範囲
}

Game::Game()
{
}

Game::~Game()
{
	Objct_DeleteGO();

	m_crystalList.clear();
	m_enemyList.clear();
	m_ghostList.clear();
}

void Game::Objct_DeleteGO()
{
	DeleteGO(m_player);
	DeleteGO(m_backGround);
	DeleteGO(m_gameCamera);
	DeleteGO(m_playerStatusGauge);

	for (int i = 0; i < m_crystalList.size(); i++) {
		DeleteGO(m_crystalList[i]);
	}

	for (int i = 0; i < m_enemyList.size(); i++) {
		DeleteGO(m_enemyList[i]);
	}

	for (int i = 0; i < m_ghostList.size(); i++) {
		DeleteGO(m_ghostList[i]);
	}
}

bool Game::Start()
{
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_circleGauge = NewGO<PressAndHoldGauge>(0, "pressAndHoldGauge");

	LevelDesign();

	//m_playerStatusGauge = NewGO<PlayerStatusGauge>(0, "playerStatusGauge");

	return true;
}

void Game::LevelDesign()
{
	m_levelRender.Init("Assets/level/levelData.tkl", [&](LevelObjeData& objData){
		// stageなら
		if (objData.EqualObjectName(L"stage") == true)
		{
			m_backGround = NewGO<BackGround>(0, "backGround");
			m_backGround->SetPosition(objData.position);
			m_backGround->SetScale(objData.scale);
			//m_backGround->SetRotation(objData.rotaition);
			return true;
		}
		// ghostなら
		if (objData.ForwardMatchName(L"ghost") == true)
		{
			PhysicsGhost* m_physicsGhost = NewGO<PhysicsGhost>(0, "physicsGhost");
			m_physicsGhost->SetPosition(objData.position);
			m_physicsGhost->SetScale(objData.scale);
			//m_physicsGhost->SetRotation(objData.rotaition);
			m_ghostList.push_back(m_physicsGhost);

			//m_pointLight.SetPosition(Vector3(objData.position.x, objData.position.y + Y_UP, objData.position.z));
			//m_pointLight.SetColor(LIGHT_COLOR);
			//m_pointLight.SetNumber(objData.number);

			return true;
		}
		// crystalなら
		if (objData.EqualObjectName(L"crystal") == true) 
		{
			Crystal* m_crystal = NewGO<Crystal>(0, "crystal");
			m_crystal->SetPosition(objData.position);
			m_crystal->SetScale(objData.scale);
			//m_crystal->SetRotation(objData.rotaition);
			m_crystal->SetTexture();

			// リストに追加
			m_crystalList.push_back(m_crystal);
			return true;
		}
		// playerなら
		if (objData.EqualObjectName(L"player") == true)
		{
			m_player = NewGO<Player>(0, "player");
			m_player->SetPosition(objData.position);
			m_player->SetRotation(objData.rotaition);
			return true;
		}
		// enemyなら
		if (objData.EqualObjectName(L"enemy") == true)
		{
			Enemy_Stone* m_bee = NewGO<Enemy_Stone>(0, "stone");
			m_bee->SetPosition(objData.position);
			m_bee->SetRotation(objData.rotaition);

			//Enemy_Slime* m_slime = NewGO<Enemy_Slime>(0, "slime");
			//m_slime->SetPosition(objData.position);
			//m_slime->SetRotation(objData.rotaition);

	/*		Enemy_Mushroom* m_mushroom = NewGO<Enemy_Mushroom>(0, "mushroom");
			m_mushroom->SetPosition(objData.position);
			m_mushroom->SetRotation(objData.rotaition);*/
			return true;
		}

		return true;
		}
	);
}

void Game::Update()
{
	// playerが死んでいるなら
	if (m_player->GetActionState() == m_player->m_enActionState_Death) {
		m_enGameState = m_enGameState_GameOver;
	}

	// ゲームをクリアしたなら
	if (m_player->GetActionState() == m_player->m_enActionState_Clear) {
		m_enGameState = m_enGameState_GameClear;
	}

	switch (m_enGameState) {
	case m_enGameState_Play:
		PlayGame();
		break;
	case m_enGameState_GameClear:
	case m_enGameState_GameOver:
		QuitGame();
		break;
	}
}

void Game::PlayGame()
{
	// playerが停止しているときは実行しない
	if (m_player->GetActionState() == m_player->m_enActionState_Idle ||
		m_player->GetActionState() == m_player->m_enActionState_Dig) {
		return;
	}

	CanDrawObject();
}

void Game::CanDrawObject()
{
	for (int i = 0; i < m_crystalList.size(); i++) {
		// 既に取得済みなら次のループに移行する
		if (m_crystalList[i]->GetCrystalState() == m_crystalList[i]->m_enCrystalStete_HavePlayer) {
			continue;
		}

		Vector3 diff = m_crystalList[i]->GetPosition() - m_player->GetPosition();

		// 長さが一定以上だったなら
		if (diff.Length() >= CANDRAW_LENGTH) {
			// 描画しない
			m_crystalList[i]->SetCrystalState(m_crystalList[i]->m_enCrystalState_NotDraw);
			continue;
		}
		// そうでないなら描画する 
		m_crystalList[i]->SetCrystalState(m_crystalList[i]->m_enCrystalStete_Normal);
	}

	for (int i = 0; i < m_enemyList.size(); i++){
		Vector3 diff = m_enemyList[i]->GetPosition() - m_player->GetPosition();

		// 長さが一定以上だったなら
		if (diff.Length() >= CANDRAW_LENGTH) {
			// 描画しない
			m_enemyList[i]->SetCanDrawFlag(false);
			continue;
		}
		// 描画しない
		m_enemyList[i]->SetCanDrawFlag(true);
	}
}

void Game::QuitGame()
{
	switch (m_enGameState) {
	case m_enGameState_GameClear:	
		m_fontRender.SetText(L"GAME CLEAR");
		break;
	case m_enGameState_GameOver:
		m_fontRender.SetText(L"GAME OVER");
		break;

	}
	m_fontRender.SetPosition({ 0.0f, 0.0f, 0.0f});

	for (int i = 0; i < m_enemyList.size(); i++) {
		m_enemyList[i]->SetEnemyState(m_enemyList[i]->m_enActionState_GameQuit);
	}

	if (g_pad[0]->IsTrigger(enButtonA)) {
		m_gameResult = NewGO<GameResult>(0, "gameResult");
		Score();
		DeleteGO(this);
	}
}

void Game::Score()
{
	std::array<int, 4> sum = { 0,0,0,0 };

	for (int i = 0; i < m_player->GetCrystalList().size(); i++) {
		// レアリティを取得
		int num = m_player->GetCrystalList()[i]->GetRarity();
		// 加算
		sum[num]++;
		// レアリティごとの個数を渡す
		m_gameResult->SetCrystalSum(num, sum[num]);
	}
}

void Game::Render(RenderContext& rc) 
{
	m_fontRender.Draw(rc);
}