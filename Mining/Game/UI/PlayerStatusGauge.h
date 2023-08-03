#pragma once

class Player;

class PlayerStatusGauge:public IGameObject
{
public:
	PlayerStatusGauge();
	~PlayerStatusGauge();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	/// <summary>
	/// 値を表示する
	/// </summary>
	void DrawGaugeValue();

	struct GaugeStatus {
		int			m_gaugeMaxValue = 0;				// 最大値
		int			m_gaugeMinValue = 0;				// 最小値
		int			m_gaugeNowValue = 0;				// 現在の値
		int			m_gaugeDrawValue = 0;				// 描画時に使用する変数
		float		m_gaugeScaleX = 0.0f;				// ゲージのスケール
	};

	/// <summary>
	/// 値を変更する
	/// </summary>
	/// <param name="gauge">値を変更するゲージ</param>
	void ChangeGaugeValue(GaugeStatus& gauge);

private:
	SpriteRender	m_spriteRenderHitPointGauge;		// スプライトレンダー(HP)
	SpriteRender	m_spriteRenderHitPointGaugeBase;	// スプライトレンダー(HP)
	SpriteRender	m_spriteRenderStaminaGauge;			// スプライトレンダー(スタミナ)
	SpriteRender	m_spriteRenderStaminaGaugeBase;		// スプライトレンダー(スタミナ)
	SpriteRender	m_spriteRenderUnityChan;			// スプライトレンダー

	FontRender		m_fontRenderHitPoint;				// フォントレンダー(HP)
	FontRender		m_fontRenderStamina;				// フォントレンダー(スタミナ)

	Player*			m_player = nullptr;					// プレイヤー

	GaugeStatus		m_hitPointGauge;					// HP
	GaugeStatus		m_staminaGauge;						// スタミナ
};

