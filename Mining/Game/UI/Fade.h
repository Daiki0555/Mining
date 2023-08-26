#pragma once
class Fade :public IGameObject
{
public:
	Fade();
	~Fade();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// フェードインの処理
	/// </summary>
	void FadeIn() {
		m_fadeState = m_enFadeState_FadeIn;
	}

	/// <summary>
	/// フェードアウトの処理
	/// </summary>
	void FadeOut() {
		m_fadeState = m_enFadeState_FadeOut;
	}

	/// <summary>
	/// フェード中かどうか。
	/// </summary>
	/// <returns></returns>
	const bool IsFade() const
	{
		return m_fadeState != m_enFadeState_Idle;
	}

	/// <summary>
	/// Loadingの文字を表示するか決定する
	/// </summary>
	/// <param name="flag">trueなら描画する</param>
	void SetDrawFlag(bool flag) 
	{
		m_isDraw = flag;
	}

private:
	/// <summary>
	/// 画像を更新
	/// </summary>
	void SpriteUpdate();

	/// <summary>
	/// 画像を回転させる
	/// </summary>
	void RotationImage();

private:
	enum enFadeState {
		m_enFadeState_FadeIn,								// フェードイン
		m_enFadeState_FadeOut,								// フェードアウト
		m_enFadeState_Idle,									// 待機中
	};
	enFadeState		m_fadeState = m_enFadeState_Idle;		// ステート

	SpriteRender	m_spriteRender;							// スプライトレンダー
	SpriteRender	m_imageSpriteRender;					// スプライトレンダー
	FontRender		m_fontRender;							// フォントレンダー

	bool			m_isDraw = true;						// 描画するかどうか
	float			m_alpha = 1.0f;							// 透明度
	float			m_timer = 0.0f;							// タイマー
};

