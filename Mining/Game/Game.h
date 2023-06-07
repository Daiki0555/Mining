#pragma once
class Player;
class Game:public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	
private:
	Player* m_Player = nullptr;		// ƒvƒŒƒCƒ„[
};

