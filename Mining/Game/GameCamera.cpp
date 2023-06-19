#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

namespace 
{
	const float		VALUE_Y = 50.0f;						// 持ち上げる値
	const float		ROTATING_VELOCITY = 1.5f;				// 回転速度
	const Vector3	VECTOR = { 0.0f, 150.0f, 300.0f };		// 始点から注視点へ向かうベクトル
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
	g_camera3D->SetNear(10.0f);
	g_camera3D->SetFar(5000.0f);

	// 始点から注視点へ向かうベクトルを設定
	m_toCameraPosition.Set(VECTOR);

	return true;
}

void GameCamera::Update()
{
	CameraSettings();												// カメラ設定
	CameraRotation();												// 回転
}

void GameCamera::CameraSettings()
{
	// 注視点
	Vector3 targetPosition = m_player->GetPosition();				// プレイヤーの座標を参照
	targetPosition.y += VALUE_Y;									// 足元の少し上に座標を持ち上げる

	Vector3 cameraPos = m_toCameraPosition;
	
	// 始点(自身の座標)
	Vector3 position = m_toCameraPosition + targetPosition;			// 注視点と始点から注視点へ向かうベクトルを加算

	g_camera3D->SetTarget(targetPosition);							// 注視点を設定
	g_camera3D->SetPosition(position);								// 始点を設定
	g_camera3D->Update();											// 更新
}

void GameCamera::CameraRotation()
{
	// 入力量を取得
	float x = g_pad[0]->GetRStickXF();

	Quaternion rotation;
	rotation.SetRotationDeg(Vector3::AxisY, ROTATING_VELOCITY * x);	// Y軸周りに回転
	rotation.Apply(m_toCameraPosition);								// 作成した回転を適用
}