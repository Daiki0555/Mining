#include "stdafx.h"
#include "EnemyBasic.h"
#include "Player.h"

namespace
{
	const float Y_POSITION = 25.0f;		// レイの高さ
	const float ADD_LENGTH = 100.0f;	// 乗算するベクトルの長さ
}

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
	m_enemyStatus.m_basicSpeed = moveSpeed;
	// キャラクターコントローラーを作成
	m_characterController.Init(radius, height, m_position);

	// スフィアコライダーを設定
	m_sphereCollider.Create(10.0f);

	return true;
}

void EnemyBasic::Move()
{
	// プレイヤーへ向かうベクトルを作成
	Vector3 moveSpeed = m_player->GetPosition() - m_position;
	moveSpeed.y = 0.0f;
	moveSpeed.Normalize();

	// プレイヤーと自身との間に壁があったら
	if (WallAndHit(m_position + (moveSpeed* ADD_LENGTH)) == false) {
		// 移動を停止する
		m_actionState = m_enActionState_Idle;
		return;
	}

	// 移動させる
	m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime() * m_enemyStatus.m_basicSpeed);

	// 回転
	Rotation(moveSpeed);
}

void EnemyBasic::Idle()
{
	// プレイヤーへ向かうベクトルを作成
	Vector3 moveSpeed = m_player->GetPosition() - m_position;
	moveSpeed.y = 0.0f;
	moveSpeed.Normalize();

	if (WallAndHit(m_position + (moveSpeed * ADD_LENGTH)) == false) {
		return;
	}

	// 移動を開始する
	m_actionState = m_enActionState_Move;
}

struct SweepResultWall :public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;		// 衝突フラグ

	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		// 壁とぶつかっていなかったら
		if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Wall) {
			// 衝突したのは壁ではない
			return 0.0f;
		}

		// 壁とぶつかったら
		// フラグをtrueにする
		isHit = true;
		return 0.0f;
	}
};

bool EnemyBasic::WallAndHit(Vector3 targetPosition)
{
	btTransform start, end;

	start.setIdentity();
	end.setIdentity();

	// 始点はエネミーの座標
	start.setOrigin(btVector3(m_position.x, Y_POSITION, m_position.z));

	// 終点はプレイヤーの座標
	end.setOrigin(btVector3(targetPosition.x, Y_POSITION, targetPosition.z));

	SweepResultWall callback;

	// コライダーを始点から終点まで動かして、
	// 衝突するかどうか調べる
	PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_sphereCollider.GetBody(),start, end, callback);

	// 壁と衝突した
	if (callback.isHit == true) {
		return false;
	}

	// 壁と衝突していない
	// プレイヤーを見つけた
	return true;
}

void EnemyBasic::Attack()
{
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

void EnemyBasic::Damege()
{
	if (m_modelRender.IsPlayingAnimation()) {
		return;
	}

	m_actionState = m_enActionState_StopAction;
}

void EnemyBasic::StopAction()
{
	m_StopTimer -= g_gameTime->GetFrameDeltaTime();

	// タイマーが0.0f以下になったら移行する
	if (m_StopTimer >= 0.0f) {
		return;
	}

	m_actionState = m_enActionState_Move;
}