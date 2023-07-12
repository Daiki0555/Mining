#pragma once

class Game;
class ScoreRanking;

class Title: public IGameObject
{
public:
	Title();
	~Title();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	/// <summary>
	/// 透過処理
	/// </summary>
	void Transparent();
	/// <summary>
	/// シーンの遷移
	/// </summary>
	void SceneChange();

private:
	enum enCursorState {
		m_enCursorState_Game,									// ゲーム
		m_enCursorState_Guide,									// 説明
		m_enCursorState_Ranking,								// ランキング
	};
	enCursorState	m_enCursorState = m_enCursorState_Game;		// 選択位置のステート

	ModelRender		m_modelRender;								// モデルレンダー
	SpriteRender	m_spriteRenderTitle;						// スプライトレンダー(背景)
	SpriteRender	m_spriteRenderMessage;						// スプライトレンダー(文字)

	Game*			m_game = nullptr;							// ゲーム
	ScoreRanking*	m_scoreRanking = nullptr;					// ランキング

	float			m_alpha = 1.0f;								// 透過値
};

