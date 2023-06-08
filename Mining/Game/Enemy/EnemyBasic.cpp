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
	enemyStatus.m_attackPower = attackPower;
	enemyStatus.m_moveSpeed = moveSpeed;
	// キャラクターコントローラーを作成
	m_characterController.Init(radius, height, m_position);

	return true;
}

void EnemyBasic::Move()
{

}

void EnemyBasic::Attack()
{
	m_actionState = m_ActionState_Attack;

	// プレイヤーに攻撃する
	m_player->Damage(enemyStatus.m_attackPower);
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

}

void EnemyBasic::Dizzy()
{

}