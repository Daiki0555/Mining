#pragma once
class Player;
class BackGround;
class GameCamera;
class Enemy_Bee;
class Enemy_Mushroom;
class Enemy_Slime;
class Game:public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Objct_NewGO();								// �I�u�W�F�N�g�̐���
	void Objct_DeleteGO();							// �I�u�W�F�N�g�̍폜
	void LevelDesign();								// ���x���f�U�C��
	
private:
	LevelRender		m_levelRender;					// ���x�������_�[

	Player*			m_player = nullptr;				// �v���C���[
	BackGround*		m_backGround = nullptr;			// �w�i
	GameCamera*		m_gameCamera = nullptr;			// �Q�[���J����
	Enemy_Bee*		m_bee = nullptr;				// Enemy_bee
	Enemy_Mushroom* m_mushroom = nullptr;			// Enemy_mushroom
	Enemy_Slime*	m_slime = nullptr;				// Enemy_slime
};

