#include "stdafx.h"
#include "EnemyBasic.h"
#include "Player.h"

EnemyBasic::EnemyBasic()
{

}

EnemyBasic::~EnemyBasic()
{

}

bool EnemyBasic::Start(int attackPower, float moveSpeed, float radius, float height)
{
	// インスタンスを探す
	m_player = FindGO<Player>("player");

	// ステータスを設定
	m_enemyStatus.m_attackPower = attackPower;
	m_enemyStatus.m_moveSpeed = moveSpeed;
	// キャラクターコントローラーを作成
	m_characterController.Init(radius, height, m_position);

	return true;
}

void EnemyBasic::Move()
{
	m_actionState = m_enActionState_Move;
}

void EnemyBasic::Attack()
{
	m_actionState = m_enActionState_Attack;

	// プレイヤーに攻撃する
	m_player->Damage(m_enemyStatus.m_attackPower);

	m_actionState = m_enActionState_StopAction;
}

void EnemyBasic::Rotation(Vector3 rotation)
{
	// 回転
	m_rotation.SetRotationYFromDirectionXZ(rotation);
	m_modelRender.SetRotaition(m_rotation);
}


void EnemyBasic::SearchPlayer()
{

}

void EnemyBasic::Damege()
{
	m_actionState = m_enActionState_Damage;

	if (m_modelRender.IsPlayingAnimation()) {
		return;
	}

	m_actionState = m_enActionState_StopAction;
}

void EnemyBasic::StopAction()
{
	m_actionState = m_enActionState_Idle;

	m_StopTimer -= g_gameTime->GetFrameDeltaTime();

	// タイマーが0.0f以下になったら移行する
	if (m_StopTimer >= 0.0f) {
		return;
	}

	m_actionState = m_enActionState_Move;
}