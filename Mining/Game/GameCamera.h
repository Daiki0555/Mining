#pragma once
class Player;
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	bool Start();
	void Update();
	void CameraSettings();								// �����_�A�n�_�A��p��ݒ肷��
	void CameraRotation();
	
private:
	Player*		m_player = nullptr;						// �v���C���[

	Vector3		m_toCameraPosition = Vector3::Zero;		// �����_����n�_�֌������x�N�g��
};