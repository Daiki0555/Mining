#pragma once

class Game;
class Ranking;
class Fade;
class Guide;

class Title : public IGameObject
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
	/// シーンの遷移
	/// </summary>
	void ChangeScene();
	/// <summary>
	/// シーンの切り替え
	/// </summary>
	void FadeScene();
	/// <summary>
	/// UVスクロールの処理
	/// </summary>
	void UVScroll();

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

	SpriteRender	m_spriteRenderTitle;								// スプライトレンダー(背景)
	SpriteRender	m_spriteRenderRogo;									// スプライトレンダー(ロゴ)
	SpriteRender	m_spriteRenderIcon;									// スプライトレンダー(アイコン)
	SpriteRender	m_spriteRenderUV;									// UVスクロール画像

	FontRender		m_StartMessage;										// 開始の文字
	FontRender		m_GameStartMessage;									// ゲーム開始の文字
	FontRender		m_RankingMessage;									// ランキング表示の文字
	FontRender		m_SystemMessage;									// システムの文字

	Level2DRender*	m_level2DRender = nullptr;							// 2Dレンダー
	Game*			m_game = nullptr;									// ゲーム
	Ranking*		m_ranking = nullptr;								// ランキング
	Fade*			m_fade = nullptr;									// フェード
	Guide*			m_guide = nullptr;									// 操作説明

	float			m_alpha = 1.0f;										// 透明度
	bool			m_isChange = false;									// 透過の切り替え
	bool			m_isWaitFadeOut = false;							// フェードアウトの待機中かどうか
};