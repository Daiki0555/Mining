#include "stdafx.h"
#include "PlayerStatusGauge.h"

#include "Player.h"

namespace
{
	const float			FONT_SHADOW_OFFSET = 2.0f;							// ピクセルのオフセット量
	const Vector4		FONT_SHADOW_COLOR = { 1.0f,1.0f,1.0f,1.0f };		// カラー

	const Vector4		FONT_COLOR = { 0.0f,0.0f,0.0f,1.0f };				// フォントカラー
	const float			FONT_SCALE = 0.6f;									// フォントのスケール

	const Vector2		SPRITE_PIVOT = { 0.0f,0.5f };						// ビポットの位置
}

PlayerStatusGauge::PlayerStatusGauge()
{
}

PlayerStatusGauge::~PlayerStatusGauge()
{
}

bool PlayerStatusGauge::Start()
{
	// インスタンスを探す
	m_player = FindGO<Player>("player");

	// 値を初期化
	m_hitPointGauge.m_gaugeMaxValue = m_player->GetHitPoint();
	m_hitPointGauge.m_gaugeMinValue = 0;
	m_hitPointGauge.m_gaugeNowValue = m_player->GetHitPoint();
	m_hitPointGauge.m_gaugeDrawValue = m_player->GetHitPoint();

	m_staminaGauge.m_gaugeMaxValue = m_player->GetStamina();
	m_staminaGauge.m_gaugeMinValue = 0;
	m_staminaGauge.m_gaugeNowValue = m_player->GetStamina();
	m_staminaGauge.m_gaugeDrawValue = m_player->GetStamina();

//--------------------------------------------------------------------------------------------

	// HPゲージ
	m_spriteRenderHitPointGauge.Init("Assets/Sprite/UI/Gauge/hpGauge.DDS", 358.0f, 48.0f);
	m_spriteRenderHitPointGauge.SetPosition({ -670.0f,380.0f,0.0f });
	m_spriteRenderHitPointGauge.SetPivot(SPRITE_PIVOT);
	m_spriteRenderHitPointGauge.SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRenderHitPointGauge.Update();

	m_spriteRenderHitPointGaugeBase.Init("Assets/Sprite/UI/Gauge/hpGauge_base.DDS", 358.0f, 48.0f);
	m_spriteRenderHitPointGaugeBase.SetPosition({ -490.0f,380.0f,0.0f });
	m_spriteRenderHitPointGaugeBase.SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRenderHitPointGaugeBase.Update();

	// スタミナ
	m_spriteRenderStaminaGauge.Init("Assets/Sprite/UI/Gauge/staminaGauge.DDS", 296.0f, 28.0f);
	m_spriteRenderStaminaGauge.SetPosition({ -653.0f,321.0f,0.0f });
	m_spriteRenderStaminaGauge.SetPivot(SPRITE_PIVOT);
	m_spriteRenderStaminaGauge.SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRenderStaminaGauge.Update();

	m_spriteRenderStaminaGaugeBase.Init("Assets/Sprite/UI/Gauge/staminaGauge_base.DDS", 324.0f, 48.0f);
	m_spriteRenderStaminaGaugeBase.SetPosition({ -505.0f,320.0f,0.0f });
	m_spriteRenderStaminaGaugeBase.SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRenderStaminaGaugeBase.Update();

	// UnityChan
	m_spriteRenderUnityChan.Init("Assets/Sprite/UI/Gauge/unity_chan.DDS", 182.0f, 181.0f);
	m_spriteRenderUnityChan.SetPosition({ -700.0f,350.0f,0.0f });
	m_spriteRenderUnityChan.SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRenderUnityChan.Update();

	return true;
}

void PlayerStatusGauge::Update()
{
	m_hitPointGauge.m_gaugeNowValue = m_player->GetHitPoint();
	m_staminaGauge.m_gaugeNowValue = m_player->GetStamina();

	ChangeGaugeValue(m_hitPointGauge);		// スケールを変更
	ChangeGaugeValue(m_staminaGauge);

	DrawGaugeValue();						// 数値を表示

	m_spriteRenderHitPointGauge.SetScale({ m_hitPointGauge.m_gaugeScaleX, 1.0f, 1.0f });
	m_spriteRenderHitPointGauge.Update();

	m_spriteRenderStaminaGauge.SetScale({ m_staminaGauge.m_gaugeScaleX,1.0f,1.0f });
	m_spriteRenderStaminaGauge.Update();
}

void PlayerStatusGauge::DrawGaugeValue()
{
	// 現在の残り体力・HPを表示する
	wchar_t HitPointText[256];
	// 桁数の指定
	swprintf_s(
		HitPointText, 256, L"HP  %03d / %d",
		m_hitPointGauge.m_gaugeDrawValue, 
		m_hitPointGauge.m_gaugeMaxValue
	);

	m_fontRenderHitPoint.SetText(HitPointText);
	m_fontRenderHitPoint.SetPosition({ -569.0f,490.0f,0.0f });
	m_fontRenderHitPoint.SetScale(FONT_SCALE);
	m_fontRenderHitPoint.SetColor(FONT_COLOR);
	m_fontRenderHitPoint.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

	// 現在の残り体力・HPを表示する
	wchar_t StaminaText[256];
	// 桁数の指定
	swprintf_s(
		StaminaText, 256, L"STAMINA  %03d / %d",
		m_staminaGauge.m_gaugeNowValue,
		m_staminaGauge.m_gaugeMaxValue
	);

	m_fontRenderStamina.SetText(StaminaText);
	m_fontRenderStamina.SetPosition({ -670.0f,420.0f,0.0f });
	m_fontRenderStamina.SetScale(FONT_SCALE);
	m_fontRenderStamina.SetColor(FONT_COLOR);
	m_fontRenderStamina.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);
}

void PlayerStatusGauge::ChangeGaugeValue(GaugeStatus& gauge)
{
	// スケールを計算
	gauge.m_gaugeScaleX = (float)gauge.m_gaugeNowValue / (float)gauge.m_gaugeMaxValue;

	// 同じ値の時は実行しない
	if (gauge.m_gaugeDrawValue == gauge.m_gaugeNowValue) {
		return;
	}

	// 現在の値以上のとき
	if (gauge.m_gaugeDrawValue > gauge.m_gaugeNowValue) {
		// 同じ値になるまで減算する
		gauge.m_gaugeDrawValue -= g_gameTime->GetFrameDeltaTime();
		return;
	}
	else if(gauge.m_gaugeDrawValue < gauge.m_gaugeNowValue) {
		// 同じ値になるまで加算する
		gauge.m_gaugeDrawValue += g_gameTime->GetFrameDeltaTime();
		return;
	}

	// 値を同じにする
	gauge.m_gaugeDrawValue = gauge.m_gaugeNowValue;
}

void PlayerStatusGauge::Render(RenderContext& rc)
{
	// HP
	m_spriteRenderHitPointGaugeBase.Draw(rc);
	m_spriteRenderHitPointGauge.Draw(rc);
	// スタミナ
	m_spriteRenderStaminaGaugeBase.Draw(rc);
	m_spriteRenderStaminaGauge.Draw(rc);
	// UnityChan
	m_spriteRenderUnityChan.Draw(rc);

	// フォントレンダー
	m_fontRenderHitPoint.Draw(rc);
	m_fontRenderStamina.Draw(rc);
}