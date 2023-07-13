#pragma once

class Game;
class Ranking;
class Fade;

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
	void TransparentProcess();
	/// <summary>
	/// カーソルの移動
	/// </summary>
	void ChangeCursor();
	/// <summary>
	/// シーンの遷移
	/// </summary>
	void ChangeScene();

private:
	enum enMessageState {
		m_enMessageState_Start,											// スタート
		m_enMessageState_Select											// セレクト
	};
	enMessageState	m_MessageState = m_enMessageState_Start;			// 表示しているメッセージ

	enum enCursorState {
		m_enCursorState_Game,											// ゲーム
		m_enCursorState_Guide,											// 説明
		m_enCursorState_Ranking,										// ランキング
	};
	enCursorState	m_CursorState = m_enCursorState_Game;				// 選択位置のステート

	ModelRender		m_modelRender;										// モデルレンダー
	SpriteRender	m_spriteRenderTitle;								// スプライトレンダー(背景)

	FontRender		m_StartMessage;										// 開始の文字
	FontRender		m_GameStartMessage;									// ゲーム開始の文字
	FontRender		m_RankingMessage;									// ランキング表示の文字
	FontRender		m_SystemMessage;									// システムの文字

	Game*			m_game = nullptr;									// ゲーム
	Ranking*		m_ranking = nullptr;								// ランキング
	Fade*			m_fade = nullptr;									// フェード

	float			m_alpha = 1.0f;										// 透明度
};

