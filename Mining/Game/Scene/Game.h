#pragma once

class Player;
class BackGround;
class GameCamera;
class PlayerStatusGauge;
class PressAndHoldGauge;
class Crystal;
class PhysicsGhost;
class EnemyBasic;
class Game:public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// オブジェクトの削除
	/// </summary>
	void Objct_DeleteGO();
	/// <summary>
	/// レベルデザイン
	/// </summary>
	void LevelDesign();
	/// <summary>
	/// プレイ中の処理
	/// </summary>
	void PlayGame();
	/// <summary>
	/// クリア時の処理
	/// </summary>
	void ClearGame();
	/// <summary>
	/// 死亡時の処理
	/// </summary>
	void OverGame();

	/// <summary>
	/// クリスタルのリストを取得する
	/// </summary>
	inline std::vector<Crystal*> GetCrystalList()
	{
		return m_crystalList;
	}

private:
	enum enGameState {
		m_enGameState_Play,												// プレイ中
		m_enGameState_GameClear,										// ゲームクリア
		m_enGameState_GameOver,											// ゲームオーバー
	};
	enGameState					m_enGameState = m_enGameState_Play;		// ゲームステート

	LevelRender					m_levelRender;							// レベルレンダー


	Player*						m_player = nullptr;						// プレイヤー
	BackGround*					m_backGround = nullptr;					// 背景
	GameCamera*					m_gameCamera = nullptr;					// ゲームカメラ
	PlayerStatusGauge*			m_playerStatusGauge = nullptr;			// プレイヤーのステータスゲージ
	PressAndHoldGauge*			m_circleGauge = nullptr;				// 円形ゲージ
	PhysicsGhost*				m_physicsGhost = nullptr;				// ゴーストオブジェクト

	std::vector<Crystal*>		m_crystalList;							// クリスタルの総数
	std::vector<EnemyBasic*>	m_enemyList;							// エネミーの総数
	std::vector<PhysicsGhost*>	m_ghostList;							// ゴーストの総数

	FontRender m_fontRender;
};

