#pragma once

class GameCamera;
class Player;
class BackGround;
class Crystal;
class PlayerStatusGauge;
class PressAndHoldGauge;
class Fade;
class EnemyBasic;
class GameResult;
class Sound;

class Game:public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();

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
	inline std::vector<Vector3> GetGoalList()
	{
		return m_goalList;
	}

	/// <summary>
	/// アニメーションが終了したかどうか設定する
	/// </summary>
	/// <param name="flag">trueならアニメーションが終了した</param>
	/// <returns></returns>
	void SetIsEndAnimationFlag(const bool flag) {
		m_isEndAnimation = flag;
	}

private:
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
	/// スコア計算
	/// </summary>
	void Score();

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
	Fade*						m_fade = nullptr;						// フェード
	Sound*						m_sound = nullptr;						// サウンド
	std::vector<Crystal*>		m_crystalList;							// クリスタルの総数
	std::vector<EnemyBasic*>	m_enemyList;							// エネミーの総数
	std::vector<Vector3>		m_goalList;								// ゴールの総数
	bool						m_isWaitFadeOut = false;				// フェードアウトの待機中かどうか
	bool						m_isEndAnimation = false;				// アニメーションが再生後かどうか
};

