#pragma once
class Player;
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	bool Start();
	void Update();
	/// <summary>
	/// �����_�A�n�_�A��p��ݒ肷��
	/// </summary>
	void CameraSettings();
	/// <summary>
	/// ��]����
	/// </summary>
	void CameraRotation();
	
private:
	Player*		m_player = nullptr;						// �v���C���[

	Vector3		m_toCameraPosition = Vector3::Zero;		// �����_����n�_�֌������x�N�g��
};