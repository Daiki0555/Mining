#pragma once

class NameEntry : public IGameObject
{
public:
	NameEntry();
	~NameEntry();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

public:
	/// <summary>
	/// スコアを設定。
	/// </summary>
	/// <param name="score"></param>
	void SetScore(const int score)
	{
		m_score = score;
	}

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

	/// <summary>
	/// 入力文字のアニメーション処理。
	/// </summary>
	void NameAnimation();

private:
	//文字のアニメーションステート。
	enum AnimationState
	{
		enState_Input,		//追加。
		enState_Erase,		//削除。
		enState_Idle,		//待機。
	};

private:
	SpriteRender	m_backGroundSpriteRender;			//背景画像。
	FontRender		m_spellFontRender[26];				//英文字。
	FontRender		m_inputNameFontRender;				//入力文字。
	FontRender		m_animFontRender;					//アニメーション用文字。
	Vector3			m_bezierPos[3];						//ベジェ曲線の座標。
	AnimationState	m_animationState = enState_Idle;	//アニメーションステート。	
	char			m_inputName[256];					//入力された名前。
	int				m_score = 0;						//スコア。
	int				m_cursor = 0;						//一列に並べた時のカーソル。
	int				m_cursorVertical = 0;				//縦カーソル。
	int				m_cursorHorizontal = 0;				//横カーソル。
	int				m_cursorOld = 0;					//前回の入力。
	int				m_inputNameNum = 0;					//文字の入力数。
	float			m_cursorTimer = 0.0f;				//カーソル用タイマー。
	float			m_animTimer = 0.0f;					//アニメーション用タイマー。
};

