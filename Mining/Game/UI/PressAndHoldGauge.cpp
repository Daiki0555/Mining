#include "stdafx.h"
#include "PressAndHoldGauge.h"
#include "Player.h"

namespace
{
	const float		CIRCLE_SIZE_MAX = 0.0f;								// 円形ゲージの最大
	const float		CIRCLE_SIZE_MIN = 360.0f;							// 円形ゲージの最小

	const Vector3	TEX_SCALE = { 1.0f,1.0f,1.0f };						// テクスチャのスケール

	const float		DECREASE_CIRCLE_ANGLE = 120.0f;						// 角度の増加速度
	const float		INCREASE_CIRCLE_ANGLE = 36.0f;						// 角度の減少速度

	const float		FONT_SCALE = 0.5f;									// フォントのスケール 
	const Vector4	FONT_COLOR = { 0.0f,0.0f,0.0f,1.0f };				// フォントのカラー
	const float		FONT_SHADOW_OFFSET = 2.0f;							// ピクセルのオフセット量
	const Vector4	FONT_SHADOW_COLOR = { 1.0f,1.0f,1.0f,1.0f };		// カラー

	const float		FONT_LEFT_X = 39.0f;								// 左に移動させる値
	const float		FONT_DOWN_Y = 8.0f;									// 下に移動させる値
}

PressAndHoldGauge::PressAndHoldGauge()
{

}

PressAndHoldGauge::~PressAndHoldGauge()
{

}

bool PressAndHoldGauge::Start()
{
	// インスタンスを探す
	m_player = FindGO<Player>("player");

	// ステータスを設定
	m_circleGauge.m_angle = CIRCLE_SIZE_MAX;
	m_circleGauge.m_maxSize = CIRCLE_SIZE_MAX;
	m_circleGauge.m_minSize = CIRCLE_SIZE_MIN;

	// 画像を設定
	m_spriteRenderCircle.Init("Assets/Sprite/UI/Gauge/pushAndHoldGauge.DDS", 100, 100);
	m_spriteRenderCircle.SetScale(TEX_SCALE);
	m_spriteRenderCircle.Update();

	m_spriteRenderCircleBase.Init("Assets/Sprite/UI/Gauge/pushAndHoldGauge_base.DDS", 109, 109);
	m_spriteRenderCircleBase.SetScale(TEX_SCALE);
	m_spriteRenderCircleBase.Update();

	return true;
}

void PressAndHoldGauge::Update()
{
	// Bボタンが押されているなら
	if (g_pad[0]->IsPress(enButtonB)) {
		m_changeGaugeValueFlag = true;
	}
	m_changeGaugeValueFlag = false;

	ChangeGaugeAngle();
	ChangeGaugePosition();
	SetFontRender();
}

void PressAndHoldGauge::ChangeGaugeAngle()
{
	// ゲージの変更
	if (m_changeGaugeValueFlag) {
		m_circleGauge.m_angle -= DECREASE_CIRCLE_ANGLE * g_gameTime->GetFrameDeltaTime();
		// max関数を使用して最大値を取得する
		m_circleGauge.m_angle = max(m_circleGauge.m_angle, CIRCLE_SIZE_MAX);
	}
	else {
		m_circleGauge.m_angle += INCREASE_CIRCLE_ANGLE * g_gameTime->GetFrameDeltaTime();
		// min関数を使用して最小値を取得する
		m_circleGauge.m_angle = min(m_circleGauge.m_minSize, CIRCLE_SIZE_MIN);
	}

	// 現在の値 - ゲージの最大値が一定以下だったとき
	if (m_circleGauge.m_angle - CIRCLE_SIZE_MAX <= 0.0001f) {
		// ゲージは最大
		m_maxGaugeValueFlag = true;
	}

	// 角度を適応
}

void PressAndHoldGauge::ChangeGaugePosition()
{
	// プレイヤーの座標を参照
	Vector3 m_worldPosition = m_player->GetPosition();
	// ワールド座標からスクリーン座標を計算
	g_camera3D->CalcScreenPositionFromWorldPosition(m_circleGauge.m_position, m_worldPosition);

	m_spriteRenderCircle.SetPosition({ m_circleGauge.m_position.x, m_circleGauge.m_position.y, 0.0f });
	m_spriteRenderCircle.Update();

	m_spriteRenderCircleBase.SetPosition({ m_circleGauge.m_position.x, m_circleGauge.m_position.y, 0.0f });
	m_spriteRenderCircleBase.Update();
}

void PressAndHoldGauge::SetFontRender()
{
	// フォントを表示する
	m_fontRender.SetText(L"B長押し");
	m_fontRender.SetPosition({ m_circleGauge.m_position.x - FONT_LEFT_X, m_circleGauge.m_position.y - FONT_DOWN_Y ,0.0f });
	m_fontRender.SetColor(FONT_COLOR);
	m_fontRender.SetScale(FONT_SCALE);
	m_fontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);
}

void PressAndHoldGauge::Render(RenderContext& rc)
{
	// クリスタルと衝突しているときに描画
	if (m_player->GetCanGetCrystalFlag()) {
		m_spriteRenderCircle.Draw(rc);
		m_spriteRenderCircleBase.Draw(rc);
		m_fontRender.Draw(rc);
	}
}
