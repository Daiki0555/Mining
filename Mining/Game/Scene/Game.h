#pragma once
class Player;
class BackGround;
class GameCamera;
class PlayerStatusGauge;
class PressAndHoldGauge;
class Crystal;
class Game:public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();

	void Objct_DeleteGO();											// オブジェクトの削除
	void LevelDesign();												// レベルデザイン
	
private:
	enum enGameState {
		m_enGameState_Play,											// プレイ中
		m_enGameState_GameClear,									// ゲームクリア
		m_enGameState_GameOver,										// ゲームオーバー
	};
	enGameState				m_enGameState = m_enGameState_Play;		// ゲームステート

	LevelRender				m_levelRender;							// レベルレンダー


	Player*					m_player = nullptr;						// プレイヤー
	BackGround*				m_backGround = nullptr;					// 背景
	GameCamera*				m_gameCamera = nullptr;					// ゲームカメラ
	PlayerStatusGauge*		m_playerStatusGauge = nullptr;			// プレイヤーのステータスゲージ
	PressAndHoldGauge*		m_circleGauge = nullptr;				// 円形ゲージ

	std::list<Crystal*>		m_crystalList;							// クリスタルの総数
};

