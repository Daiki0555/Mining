#pragma once
class Player;
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	bool Start();
	void Update();
	void CameraSettings();								// 注視点、始点、画角を設定する
	void CameraRotation();
	
private:
	Player*		m_player = nullptr;						// プレイヤー

	Vector3		m_toCameraPosition = Vector3::Zero;		// 注視点から始点へ向かうベクトル
};