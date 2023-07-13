#pragma once

class Game;
class Ranking;

class Title: public IGameObject
{
public:
	Title();
	~Title();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	/// <summary>
	/// カーソルの移動
	/// </summary>
	void ChangeCursor();
	/// <summary>
	/// シーンの遷移
	/// </summary>
	void ChangeScene();

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
	Ranking*		m_ranking = nullptr;						// ランキング
	Fade*			m_fade = nullptr;							// フェード

	float			m_alpha = 1.0f;								// 透過値
};

