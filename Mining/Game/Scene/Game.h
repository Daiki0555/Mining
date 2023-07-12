#pragma once

class GameResult;
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
	/// ゲーム中の処理
	/// </summary>
	void PlayGame();
	/// <summary>
	/// 描画の有無を決定する
	/// </summary>
	void CanDrawObject();
	/// <summary>
	/// ゲームの終了処理
	/// </summary>
	void QuitGame();
	/// <summary>
	/// クリア時の処理
	/// </summary>
	void GameClear();
	// ゲームオーバー時の処理
	void GameOver();
	/// <summary>
	/// スコア計算
	/// </summary>
	void Score();

	/// <summary>
	/// クリスタルのリストを取得する
	/// </summary>
	inline std::vector<Crystal*> GetCrystalList()
	{
		return m_crystalList;
	}

	/// <summary>
	/// ゴーストのリストを取得する
	/// </summary>
	/// <returns></returns>
	inline std::vector<PhysicsGhost*> GetGhostList()
	{
		return m_ghostList;
	}

private:
	enum enGameState {
		m_enGameState_Play,												// プレイ中
		m_enGameState_GameClear,										// ゲームクリア
		m_enGameState_GameOver,											// ゲームオーバー
	};
	enGameState					m_enGameState = m_enGameState_Play;		// ゲームステート

	LevelRender					m_levelRender;							// レベルレンダー

	GameResult*					m_gameResult = nullptr;					// リザルト画面
	Player*						m_player = nullptr;						// プレイヤー
	BackGround*					m_backGround = nullptr;					// 背景
	GameCamera*					m_gameCamera = nullptr;					// ゲームカメラ
	PlayerStatusGauge*			m_playerStatusGauge = nullptr;			// プレイヤーのステータスゲージ
	PressAndHoldGauge*			m_circleGauge = nullptr;				// 円形ゲージ

	std::vector<Crystal*>		m_crystalList;							// クリスタルの総数
	std::vector<EnemyBasic*>	m_enemyList;							// エネミーの総数
	std::vector<PhysicsGhost*>	m_ghostList;							// ゴーストの総数

	FontRender					m_fontRender;
};

