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
	LevelRender		m_levelRender;					// レベルレンダー

	Player*			m_player = nullptr;				// プレイヤー
	BackGround*		m_backGround = nullptr;			// 背景
};

