#pragma once
class GaugeBasic:public IGameObject
{
public:
	GaugeBasic();
	~GaugeBasic();

	bool Start(int value);
	void DrawGaugeValue(int value);
	void ChangeGaugeValue(int value);

	enum enGaugeState {
		enGaugeState_IncreaseStart,			// ゲージ増加開始
		enGaugeState_IncreaseEnd,			// ゲージ増加終了
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
	enGaugeState	m_enGaugeState;			// ステート

	SpriteRender	m_spriteRender;			// スプライトレンダー
	FontRender		m_fontRender;			// フォントレンダー

	int				m_gaugeMaxValue = 0;	// 最大値
	int				m_gaugeMinValue = 0;	// 最小値
	int				m_gaugeNowValue = 0;	// 現在の値
};

