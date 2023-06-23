#pragma once
class Player;
class PressAndHoldGauge:public IGameObject
{
public:
	PressAndHoldGauge();
	~PressAndHoldGauge();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void ChangeGaugeAngle();							// ゲージの角度を変更
	void ChangeGaugePosition();							// ゲージの座標を変更
	void SetFontRender();								// フォントレンダーの表示

private:
	SpriteRender	m_spriteRenderCircle;				// スプライトレンダー
	SpriteRender	m_spriteRenderCircleBase;			// スプライトレンダー(ベース)
	
	FontRender		m_fontRender;						// フォントレンダー

	Player*			m_player = nullptr;					// プレイヤー

	bool			m_changeGaugeValueFlag = false;		// trueなら増加、falseなら減少させる
	bool			m_maxGaugeValueFlag = false;		// 値が最大かどうか

	struct GaugeStatus {
		Vector2		m_position = Vector2::Zero;			// 座標
		float		m_angle = 0.0f;						// ゲージの角度
		float		m_maxSize = 0.0f;					// ゲージの最大
		float		m_minSize = 0.0f;					// ゲージの最小
	};
	GaugeStatus		m_circleGauge;						// 円形ゲージのステータス
};

