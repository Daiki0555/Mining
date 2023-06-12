#pragma once
class Player;
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	bool Start();
	void UpDate();
	void CameraSettings();							// 注視点、始点、画角を設定する
	
private:
	Player*		m_player = nullptr;					// プレイヤー
};

