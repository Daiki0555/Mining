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

private:
	/// <summary>
	/// 画像を更新
	/// </summary>
	void SpriteUpdate();

private:
	enum enFadeState {
		m_enFadeState_FadeIn,								// フェードイン
		m_enFadeState_FadeOut,								// フェードアウト
		m_enFadeState_Idle,									// 待機中
	};
	enFadeState		m_fadeState = m_enFadeState_Idle;		// ステート

	SpriteRender	m_spriteRender;							// スプライトレンダー
	float			m_alpha = 1.0f;							// 透明度
};

