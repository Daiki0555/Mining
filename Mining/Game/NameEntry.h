#pragma once

class NameEntry : public IGameObject
{
public:
	NameEntry();
	~NameEntry();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	/// <summary>
	/// 入力処理。
	/// </summary>
	void Input();

	/// <summary>
	/// カーソルの更新処理。
	/// </summary>
	void CursorUpdate();

	/// <summary>
	/// 名前の入力処理。
	/// </summary>
	void InputName();

	/// <summary>
	/// 名前の削除処理。
	/// </summary>
	void EraseName();

	/// <summary>
	/// 名前の更新処理。
	/// </summary>
	void NameUpdate();

	/// <summary>
	/// 終了処理。
	/// </summary>
	void End();

	/// <summary>
	/// カーソルのアニメーション処理。
	/// </summary>
	void CursorAnimation();

private:
	SpriteRender	m_backGroundSpriteRender;		//背景画像。
	FontRender		m_spellFontRender[26];			//英文字。
	FontRender		m_inputNameFontRender;			//入力文字。
	char			m_inputName[256];				//入力された名前。
	int				m_score = 13;					//スコア。
	int				m_cursor = 0;					//一列に並べた時のカーソル。
	int				m_cursorVertical = 0;			//縦カーソル。
	int				m_cursorHorizontal = 0;			//横カーソル。
	int				m_cursorOld = 0;				//前回の入力。
	int				m_inputNameNum = 0;				//文字の入力数。
	float			m_cursorTimer = 0.0f;			//カーソル用タイマー。

	FontRender m_debugFontRender;
};

