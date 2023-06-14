#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Stage/BackGround.h"
#include "GameCamera.h"
#include "Enemy/Enemy_Bee.h"
#include "Enemy/Enemy_Mushroom.h"
#include "Enemy/Enemy_Slime.h"

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
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
}

void Game::LevelDesign()
{
	// ���x���f�U�C������
	m_levelRender.Init("Assets/level/levelData.tkl", [&](LevelObjeData& objData){
		//���O��stage�̎�
		if (objData.EqualObjectName(L"stage") == true)
		{
			// �w�i��`��
			m_backGround = NewGO<BackGround>(0, "backGround");
			m_backGround->SetPosition(objData.position);
			m_backGround->SetScale(objData.scale);
			m_backGround->SetRotation(objData.rotaition);
			return true;
		}
		//���O��player�̎�
		if (objData.EqualObjectName(L"player") == true)
		{
			// �v���C���[�𐶐�
			m_player = NewGO<Player>(0, "player");
			m_player->SetPosition(objData.position);
			m_player->SetRotation(objData.rotaition);
			return true;
		}
		if (objData.EqualObjectName(L"enemy") == true)
		{
			//m_bee = NewGO<Enemy_Bee>(0, "bee");
			//m_bee->SetPosition(objData.position);
			//m_bee->SetRotation(objData.rotaition);

			//m_slime = NewGO<Enemy_Slime>(0, "slime");
			//m_slime->SetPosition(objData.position);
			//m_slime->SetRotation(objData.rotaition);

			m_mushroom = NewGO<Enemy_Mushroom>(0, "mushroom");
			m_mushroom->SetPosition(objData.position);
			m_mushroom->SetRotation(objData.rotaition);
		}

		return true;
		}
	);
}