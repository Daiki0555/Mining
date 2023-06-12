#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

namespace 
{
	float VALUE_Y = 150.0f;		// 持ち上げる値
	float VALUE_Z = 200.0f;		// 手前に移動する値
}

GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	// 近平面・遠平面の設定
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);

	// インスタンスを探す
	m_player = FindGO<Player>("player");
}

void GameCamera::UpDate()
{
	CameraSettings();							// カメラ設定
}

void GameCamera::CameraSettings()
{
	// 注視点
	Vector3 m_targetPosition = Vector3::Zero;
	m_targetPosition = m_player->GetPosition();	// プレイヤーの座標を参照
	m_targetPosition.y += VALUE_Y;				// 足元の少し上に座標を持ち上げる

	g_camera3D->SetTarget(m_targetPosition);	// 注視点を設定


	// 始点(自身の座標)
	Vector3 m_cameraPosition = Vector3::Zero;
	m_cameraPosition = m_player->GetPosition();	// プレイヤーの座標を参照
	m_cameraPosition.z -= VALUE_Z;				// 注視点の手前に移動する

	g_camera3D->SetPosition(m_cameraPosition);	// 始点を設定

}