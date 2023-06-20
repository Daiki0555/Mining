#include "stdafx.h"
#include "GaugeBasic.h"

namespace
{
	const Vector3		FONT_POSITION = { 0.0f,0.0f,0.0f };				// フォントの座標
	const float			FONT_SCALE = 1.0f;								// フォントのスケール
	const float			FONT_SHADOW_OFFSET = 2.0f;						// ピクセルのオフセット量
	const Vector4		FONT_SHADOW_COLOR = { 1.0f,1.0f,1.0f,1.0f };	// カラー
}

GaugeBasic::GaugeBasic()
{
}

GaugeBasic::~GaugeBasic()
{
}

bool GaugeBasic::Start(int value)
{
	m_gaugeMaxValue = value;		// 最大値を設定
	m_gaugeNowValue = value;		// 現在の値を設定する

	return true;
}

void GaugeBasic::DrawGaugeValue(int value)
{
	m_gaugeNowValue -= value;

	// 現在の残り体力・HPを表示する
	wchar_t text[256];
	// 桁数の指定
	swprintf_s(text, 256, L"%d / %d", m_gaugeNowValue,m_gaugeMaxValue);

	m_fontRender.SetText(text);
	m_fontRender.SetPosition(FONT_POSITION);
	m_fontRender.SetScale(FONT_SCALE);
	m_fontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);
}

void GaugeBasic::ChangeGaugeValue(int value)
{
	int sum = 0;
	int num = 1;

	if (enGaugeState_DecrementStart) {
		m_gaugeNowValue -= num;
	}
	else {
		m_gaugeNowValue += num;
	}

	sum += num;

	// sumが設定した値以上になったとき
	if (sum >= value) {
		sum = value;

		if (enGaugeState_DecrementStart) {
			m_enGaugeState = enGaugeState_DecrementEnd;
			return;
		}
		m_enGaugeState = enGaugeState_IncreaseEnd;
	}
}
