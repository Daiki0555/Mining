#pragma once
class Player;
class Gauge:public IGameObject
{
public:
	Gauge();
	~Gauge();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void DrawGaugeValue();

	struct GaugeStatus {
		int			m_gaugeMaxValue = 0;				// 最大値
		int			m_gaugeMinValue = 0;				// 最小値
		int			m_gaugeNowValue = 0;				// 現在の値
		int			m_gaugeDrawValue = 0;				// 描画時に使用する変数
		float		m_gaugeScaleX = 0.0f;				// ゲージのスケール
	};

	void ChangeGaugeValue(GaugeStatus& gauge);

	enum enGaugeState {
		enGaugeState_IncreaseStart,			// ゲージ増加開始
		enGaugeState_IncreaseEnd,			// ゲージ増加終了s
		enGaugeState_DecrementStart,		// ゲージ減少開始
		enGaugeState_DecrementEnd			// ゲージ減少終了
	};

	/// <summary>
	/// ステートを設定する
	/// </summary>
	void SetGaugeState(enGaugeState state) {
		m_enGaugeState = state;
	}

	/// <summary>
	/// 現在のステートを返す
	/// </summary>s
	const enGaugeState GetGaugeState() const{
		return m_enGaugeState;
	}

private:
	SpriteRender	m_spriteRenderHitPointGauge;		// スプライトレンダー(HP)
	SpriteRender	m_spriteRenderHitPointGaugeBase;	// スプライトレンダー(HP)
	SpriteRender	m_spriteRenderStaminaGauge;			// スプライトレンダー(スタミナ)
	SpriteRender	m_spriteRenderStaminaGaugeBase;		// スプライトレンダー(スタミナ)
	SpriteRender	m_spriteRenderUnityChan;			// スプライトレンダー

	FontRender		m_fontRenderHitPoint;				// フォントレンダー(HP)
	FontRender		m_fontRenderStamina;				// フォントレンダー(スタミナ)

	enGaugeState	m_enGaugeState;						// ステート

	Player*			m_player = nullptr;					// プレイヤー

	GaugeStatus		m_hitPointGauge;					// HP
	GaugeStatus		m_staminaGauge;						// スタミナ
};

