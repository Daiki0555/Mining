#pragma once
class Player;
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	bool Start();
	void UpDate();
	void CameraSettings();							// �����_�A�n�_�A��p��ݒ肷��
	
private:
	Player*		m_player = nullptr;					// �v���C���[
};

