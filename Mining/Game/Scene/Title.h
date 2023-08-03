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

private:
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

private:
	enum enMessageState {
		m_enMessageState_Start,											// スタート
		m_enMessageState_Select											// セレクト
	};
	enMessageState	m_MessageState = m_enMessageState_Start;			// 表示しているメッセージ

public:
	enum enCursorState {
		m_enCursorState_Game,											// ゲーム
		m_enCursorState_Guide,											// 説明
		m_enCursorState_Ranking,										// ランキング
	};

private:
	enCursorState	m_CursorState = m_enCursorState_Game;				// 選択位置のステート

public:
	/// <summary>
	/// カーソル位置のステートを設定する
	/// </summary>
	/// <param name="state"></param>
	void SetCursorScene(const enCursorState state) {
		m_MessageState = m_enMessageState_Select;						// セレクト画面を表示
		m_CursorState = state;											// 選択位置のステートを設定
	}

private:
	SpriteRender	m_spriteRenderTitle;								// スプライトレンダー(背景)
	SpriteRender	m_spriteRenderRogo;									// スプライトレンダー(ロゴ)
	SpriteRender	m_spriteRenderIcon;									// スプライトレンダー(アイコン)
	SpriteRender	m_spriteRenderUV;									// スプライトレンダー(UVスクロール画像)

	FontRender		m_StartMessage;										// 開始の文字
	FontRender		m_GameStartMessage;									// ゲーム開始の文字
	FontRender		m_RankingMessage;									// ランキング表示の文字
	FontRender		m_SystemMessage;									// システムの文字

	Level2DRender*	m_level2DRender = nullptr;							// 2Dレンダー
	Game*			m_game = nullptr;									// ゲーム
	Ranking*		m_ranking = nullptr;								// ランキング
	Fade*			m_fade = nullptr;									// フェード
	Guide*			m_guide = nullptr;									// 操作説明

	bool			m_isChange = false;									// 透過の切り替え
	bool			m_isWaitFadeOut = false;							// フェードアウトの待機中かどうか
	float			m_alpha = 1.0f;										// 透明度
	float			m_uvTimer = 0.0f;									// UVスクロール用タイマー
};