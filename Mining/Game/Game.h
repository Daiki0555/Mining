#pragma once
class Player;
class BackGround;
class Game:public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void LevelDesign();
	
private:
	LevelRender		m_levelRender;					// ���x�������_�[

	Player*			m_player = nullptr;				// �v���C���[
	BackGround*		m_backGround = nullptr;			// �w�i
};

