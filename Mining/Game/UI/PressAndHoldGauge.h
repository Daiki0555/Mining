#pragma once
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

	/// <summary>
	/// 描画するかどうかのフラグを設定する
	/// </summary>
	/// <param name="flag">trueなら描画</param>
	void SetCanDrawGauge(bool flag) {
		m_canDrawGaugeFlag = flag;
	}

	/// <summary>
	/// 角度を変更するかどうかのフラグを設定する
	/// </summary>
	/// <param name="flag">trueなら減少させる</param>
	void SetChangeGaugeAngle(bool flag) {
		m_changeGaugeAngleFlag = flag;
	}

	/// <summary>
	/// 座標を設定する
	/// </summary>
	/// <param name="position">3D座標</param>
	void Set3DPosition(Vector3 position) {
		m_circleGauge.m_3Dposition = position;
	}

	enum enGaugeState {
		enGaugeState_Max,								// ゲージ最大
		enGaugeState_Min,								// ゲージ最小
		enGaugeState_Increase,							// ゲージ増加中
		enGaugeState_Decrease							// ゲージ減少中
	};

	/// <summary>
	/// 現在のステートを取得する
	/// </summary>
	/// <returns></returns>
	const enGaugeState GetNowStatus() const {
		return m_enGaugeState;
	}

private:
	SpriteRender	m_spriteRenderCircle;				// スプライトレンダー
	SpriteRender	m_spriteRenderCircleBase;			// スプライトレンダー(ベース)
	SpriteRender	m_spriteRenderCircleBack;			// スプライトレンダー(背景)
	
	FontRender		m_fontRender;						// フォントレンダー

	struct GaugeStatus {
		Vector3		m_3Dposition = Vector3::Zero;		// 3D座標
		Vector2		m_2Dposition = Vector2::Zero;		// 2D座標
		float		m_angle = 0.0f;						// ゲージの角度(初期値)
		float		m_maxSize = 0.0f;					// ゲージの最大
		float		m_minSize = 0.0f;					// ゲージの最小
	};
	GaugeStatus		m_circleGauge;						// 円形ゲージのステータス

	enGaugeState	m_enGaugeState = enGaugeState_Min;	// ゲージの今のステート

	bool			m_changeGaugeAngleFlag = false;		// trueなら増加、falseなら減少させる
	bool			m_canDrawGaugeFlag = false;			// 描画できるかどうか
};