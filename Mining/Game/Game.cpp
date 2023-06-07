#include "stdafx.h"
#include "Game.h"
#include "Player.h"

Game::Game()
{
}

Game::~Game()
{
	DeleteGO(m_Player);
}

bool Game::Start()
{
	m_Player = NewGO<Player>(0, "player");
	return true;
}