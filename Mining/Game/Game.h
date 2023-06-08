#pragma once
class Player;
class Game:public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void LevelDesign();
	
private:
	//LevelRender m_levelRender;

	Player* m_Player = nullptr;		// ƒvƒŒƒCƒ„[
};

