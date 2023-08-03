#pragma once
class Player;
class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	bool Start();
	void Update();

private:
	/// <summary>
	/// �����_�A�n�_�A��p��ݒ肷��
	/// </summary>
	void CameraSettings();
	/// <summary>
	/// ��]����
	/// </summary>
	void CameraRotation();

	Player*		m_player = nullptr;						// �v���C���[
	Vector3		m_toCameraPosition = Vector3::Zero;		// �����_����n�_�֌������x�N�g��
};