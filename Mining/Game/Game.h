#pragma once
class Player;
class BackGround;
class GameCamera;
class Game:public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Objct_NewGO();								// オブジェクトの生成
	void Objct_DeleteGO();							// オブジェクトの削除
	void LevelDesign();								// レベルデザイン
	
private:
	LevelRender		m_levelRender;					// レベルレンダー

	Player*			m_player = nullptr;				// プレイヤー
	BackGround*		m_backGround = nullptr;			// 背景
	GameCamera*		m_gameCamera = nullptr;			// ゲームカメラ
};

