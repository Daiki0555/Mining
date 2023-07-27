#include "stdafx.h"
#include "PressAndHoldGauge.h"

namespace
{
	const Vector3	TEX_SCALE = Vector3(1.0f, 1.0f, 1.0f);				// テクスチャのスケール

	const float		DECREASE_CIRCLE_ANGLE = 36.0f;						// 角度の減少速度
	const float		INCREASE_CIRCLE_ANGLE = 180.0f;						// 角度の増加速度

	const float		FONT_SCALE = 0.5f;									// フォントのスケール 
	const float		FONT_SHADOW_OFFSET = 2.0f;							// ピクセルのオフセット量
	const Vector4	FONT_SHADOW_COLOR = Vector4(1.0f, 1.0f, 1.0f, 1.0f);// カラー

	const float		FONT_LEFT_X = 39.0f;								// 左に移動させる値
	const float		FONT_DOWN_Y = 8.0f;									// 下に移動させる値

	const float		PI = 3.14159;										// 円周率

	const float		CHANGE_STATE_TIME = 10.0f;							// ステートを変更する待ち時間
}

PressAndHoldGauge::PressAndHoldGauge()
{

}

PressAndHoldGauge::~PressAndHoldGauge()
{

}

bool PressAndHoldGauge::Start()
{
	// 画像を設定
	m_spriteRenderCircle.Init("Assets/Sprite/UI/Gauge/pushAndHoldGauge.DDS", 100, 100, AlphaBlendMode_Trans, 1);
	m_spriteRenderCircle.SetScale(TEX_SCALE);
	m_spriteRenderCircle.Update();

	m_spriteRenderCircleBase.Init("Assets/Sprite/UI/Gauge/pushAndHoldGauge_base.DDS", 109, 109);
	m_spriteRenderCircleBase.SetScale(TEX_SCALE);
	m_spriteRenderCircleBase.Update();

	m_spriteRenderCircleBack.Init("Assets/Sprite/UI/Gauge/pushAndHoldGauge_back.DDS", 109, 109);
	m_spriteRenderCircleBack.SetScale(TEX_SCALE);
	m_spriteRenderCircleBack.Update();

	RenderingEngine::GetInstance()->GetSpriteCB().clipSize.y = (m_circleGauge.m_angle * PI) / 180.0f;

	return true;
}

void PressAndHoldGauge::Update()
{
	if (m_canDrawGaugeFlag == false) {
		return;
	}

	ChangeGaugeAngle();
	ChangeGaugePosition();
	SetFontRender();
}

void PressAndHoldGauge::ChangeGaugeAngle()
{
	// ゲージの変更
	if (m_changeGaugeAngleFlag) {
		// ステートを変更
		m_enGaugeState = enGaugeState_Increase;
		// 値を増加
		m_circleGauge.m_angle += INCREASE_CIRCLE_ANGLE * g_gameTime->GetFrameDeltaTime();
		// min関数を使用して最小値を取得する
		m_circleGauge.m_angle = min(m_circleGauge.m_angle, CIRCLE_SIZE_MIN);
	}
	else{
		// ステートを変更
		m_enGaugeState = enGaugeState_Decrease;
		// 値を減少
		m_circleGauge.m_angle -= DECREASE_CIRCLE_ANGLE * g_gameTime->GetFrameDeltaTime();
		// max関数を使用して最大値を取得する
		m_circleGauge.m_angle = max(m_circleGauge.m_angle, CIRCLE_SIZE_MAX);
	}

	// ゲージの最大値が一定以上だったとき
	if (m_circleGauge.m_angle >= CIRCLE_SIZE_MIN) {
		// ゲージは最小(360)
		m_enGaugeState = enGaugeState_Min;
	}
	else if(m_circleGauge.m_angle <= CIRCLE_SIZE_MAX) {
		// ゲージは最大(0)
		m_enGaugeState = enGaugeState_Max;
	}

	// 角度を適応
	RenderingEngine::GetInstance()->GetSpriteCB().clipSize.y = (m_circleGauge.m_angle * PI) / 180.0f;
}

void PressAndHoldGauge::ChangeGaugePosition()
{
	// プレイヤーの座標を参照
	Vector3 m_worldPosition = m_circleGauge.m_3Dposition;
	// ワールド座標からスクリーン座標を計算
	g_camera3D->CalcScreenPositionFromWorldPosition(m_circleGauge.m_2Dposition, m_worldPosition);

	// 座標を設定する
	m_spriteRenderCircle.SetPosition({ m_circleGauge.m_2Dposition.x, m_circleGauge.m_2Dposition.y, 0.0f });
	m_spriteRenderCircle.Update();

	m_spriteRenderCircleBase.SetPosition({ m_circleGauge.m_2Dposition.x, m_circleGauge.m_2Dposition.y, 0.0f });
	m_spriteRenderCircleBase.Update();

	m_spriteRenderCircleBack.SetPosition({ m_circleGauge.m_2Dposition.x, m_circleGauge.m_2Dposition.y, 0.0f });
	m_spriteRenderCircleBack.Update();
}

void PressAndHoldGauge::SetFontRender()
{
	// フォントを表示する
	m_fontRender.SetText(L"B長押し");
	m_fontRender.SetPosition({ m_circleGauge.m_2Dposition.x - FONT_LEFT_X, m_circleGauge.m_2Dposition.y - FONT_DOWN_Y ,0.0f });
	m_fontRender.SetColor(Vector4::Black);
	m_fontRender.SetScale(FONT_SCALE);
	m_fontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);
}

void PressAndHoldGauge::Render(RenderContext& rc)
{
	if (m_canDrawGaugeFlag) {
		m_spriteRenderCircleBack.Draw(rc);
		m_spriteRenderCircle.Draw(rc);
		m_spriteRenderCircleBase.Draw(rc);
		m_fontRender.Draw(rc);
	}
}
