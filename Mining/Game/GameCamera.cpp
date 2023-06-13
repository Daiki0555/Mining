#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

namespace 
{
	const float		VALUE_Y = 150.0f;						// 持ち上げる値

	const Vector3	VECTOR = { 0.0f, 150.0f, -300.0f };		// 始点から注視点へ向かうベクトル
}

GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	// インスタンスを探す
	m_player = FindGO<Player>("player");

	// 近平面・遠平面の設定
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);

	// 始点から注視点へ向かうベクトルを設定
	m_toCameraPosition.Set(VECTOR);

	return true;
}

void GameCamera::Update()
{
	CameraSettings();												// カメラ設定
}

void GameCamera::CameraSettings()
{
	// 注視点
	Vector3 targetPosition = m_player->GetPosition();				// プレイヤーの座標を参照
	targetPosition.y += VALUE_Y;									// 足元の少し上に座標を持ち上げる

	// 始点(自身の座標)
	Vector3 position = m_toCameraPosition + targetPosition;			// 注視点と始点から注視点へ向かうベクトルを加算

	g_camera3D->SetTarget(targetPosition);							// 注視点を設定
	g_camera3D->SetPosition(position);								// 始点を設定
	g_camera3D->Update();											// 更新
}