#pragma once
class Player;
class BackGround;
class GameCamera;
class Gauge;
class Game:public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Objct_DeleteGO();							// �I�u�W�F�N�g�̍폜
	void LevelDesign();								// ���x���f�U�C��
	
private:
	LevelRender		m_levelRender;					// ���x�������_�[

	Player*			m_player = nullptr;				// �v���C���[
	BackGround*		m_backGround = nullptr;			// �w�i
	GameCamera*		m_gameCamera = nullptr;			// �Q�[���J����
	Gauge*			m_gauge = nullptr;				// �Q�[�W
};

