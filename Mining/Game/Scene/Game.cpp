#include "stdafx.h"
#include "Game.h"

#include "Scene/GameResult.h"
#include "Player.h"
#include "Stage/BackGround.h"
#include "GameCamera.h"
#include "Enemy/Enemy_Bee.h"
#include "Enemy/Enemy_Mushroom.h"
#include "Enemy/Enemy_Slime.h"
#include "Stage/Object/Crystal.h"
#include "UI/PlayerStatusGauge.h"
#include "UI/PressAndHoldGauge.h"
#include "Stage/PhysicsGhost.h"

namespace
{
	const Vector3	LIGHT_COLOR = { 10.0f,10.0f,10.0f };		// ���C�g�̃J���[
	const float		Y_UP = 0.0f;								// �|�C���g���C�g������グ��l

	const float		CANDRAW_LENGTH = 3500.0f;					// �`��ł��鋗��
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

	m_playerStatusGauge = NewGO<PlayerStatusGauge>(0, "playerStatusGauge");

	return true;
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
			//m_backGround->SetRotation(objData.rotaition);
			return true;
		}
		// ���O��ghost�̂Ƃ�
		if (objData.ForwardMatchName(L"ghost") == true)
		{
			// �S�[�X�g��쐬
			PhysicsGhost* m_physicsGhost = NewGO<PhysicsGhost>(0, "physicsGhost");
			m_physicsGhost->SetPosition(objData.position);
			m_physicsGhost->SetScale(objData.scale);
			//m_physicsGhost->SetRotation(objData.rotaition);
			m_ghostList.push_back(m_physicsGhost);

			//// �|�C���g���C�g��z�u
			//m_pointLight.SetPosition(Vector3(objData.position.x, objData.position.y + Y_UP, objData.position.z));
			//m_pointLight.SetColor(LIGHT_COLOR);
			//m_pointLight.SetNumber(objData.number);

			return true;
		}
		// ���O��crystal�̂Ƃ�
		if (objData.EqualObjectName(L"crystal") == true) 
		{
			// �I�u�W�F�N�g��쐬
			Crystal* m_crystal = NewGO<Crystal>(0, "crystal");
			m_crystal->SetPosition(objData.position);
			m_crystal->SetScale(objData.scale);
			//m_crystal->SetRotation(objData.rotaition);
			m_crystal->SetTexture();

			// ������ǉ�
			m_crystalList.push_back(m_crystal);
			return true;
		}
		//���O��player�̎�
		if (objData.EqualObjectName(L"player") == true)
		{
			// �v���C���[��쐬
			m_player = NewGO<Player>(0, "player");
			m_player->SetPosition(objData.position);
			m_player->SetRotation(objData.rotaition);
			return true;
		}
		// ���O��enemy�̂Ƃ�
		if (objData.EqualObjectName(L"enemy") == true)
		{
			//Enemy_Bee* m_bee = NewGO<Enemy_Bee>(0, "bee");
			//m_bee->SetPosition(objData.position);
			//m_bee->SetRotation(objData.rotaition);

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
	// �v���C���[�����S���Ă���Ȃ�
	if (m_player->GetActionState() == m_player->m_enActionState_Death) {
		// �Q�[���I�[�o�[
		m_enGameState = m_enGameState_GameOver;
	}

	// �S�[���ɂ��ǂ蒅�����Ȃ�
	if (m_player->GetActionState() == m_player->m_enActionState_Clear) {
		// �Q�[���N���A
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
	// player���̍��W���ϓ����Ă��Ȃ��Ƃ��͎��s���Ȃ�
	if (m_player->GetActionState() == m_player->m_enActionState_Idle ||
		m_player->GetActionState() == m_player->m_enActionState_Dig) {
		return;
	}

	CanDrawObject();
}

void Game::CanDrawObject()
{
	for (int i = 0; i < m_crystalList.size(); i++) {
		// ���Ɏ擾����Ă����ԂȂ�v�Z�͂��Ȃ�
		if (m_crystalList[i]->GetCrystalState() == m_crystalList[i]->m_enCrystalStete_HavePlayer) {
			continue;
		}

		Vector3 diff = m_crystalList[i]->GetPosition() - m_player->GetPosition();

		// ���������ȏ�Ȃ�
		if (diff.Length() >= CANDRAW_LENGTH) {
			// �`��͂��Ȃ�
			m_crystalList[i]->SetCrystalState(m_crystalList[i]->m_enCrystalState_NotDraw);
			continue;
		}
		// �`��͂��Ȃ�
		m_crystalList[i]->SetCrystalState(m_crystalList[i]->m_enCrystalStete_Normal);
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

	if (g_pad[0]->IsTrigger(enButtonA)) {
		// ���U���g�Ɉڍs
		m_gameResult = NewGO<GameResult>(0, "gameResult");
		Score();
		DeleteGO(this);
	}
}

void Game::Score()
{
	std::array<int, 4> sum = { 0,0,0,0 };

	for (int i = 0; i < m_player->GetCrystalList().size(); i++) {
		// ���A�x��擾
		int num = m_player->GetCrystalList()[i]->GetRarity();
		// �l����Z
		sum[num]++;
		// ���A�x�ʂ̎擾����ݒ�
		m_gameResult->SetCrystalSum(num, sum[num]);
	}
}

void Game::Render(RenderContext& rc) 
{
	m_fontRender.Draw(rc);
}