#include "stdafx.h"
#include "Fade.h"

Fade::Fade()
{

}

Fade::~Fade()
{

}

bool Fade::Start()
{
	m_spriteRender.Init("Assets/sprite/UI/Scene/Fade.DDS", 1920.0f, 1080.0f);

	return true;
}

void Fade::Update()
{
	switch (m_fadeState) {
	case m_enFadeState_FadeIn:
		// 透明度を減らす
		m_alpha -= 1.0f * g_gameTime->GetFrameDeltaTime();

		if (m_alpha < 0.0f) {
			m_alpha = 0.0f;						// 補正
			m_fadeState = m_enFadeState_Idle;	// 待機状態に移行
		}
		break;
	case m_enFadeState_FadeOut:
		// 透明度を増やす
		m_alpha += 1.0f * g_gameTime->GetFrameDeltaTime();

		if (m_alpha > 1.0f) {
			m_alpha = 1.0f;						// 補正
			m_fadeState = m_enFadeState_Idle;	// 待機状態に移行
		}
		break;
	case m_enFadeState_Idle:
		break;
	}

	SpriteUpdate();
}

void Fade::SpriteUpdate()
{
	Vector4 alpha = Vector4{ 1.0f,1.0f,1.0f,m_alpha };

	// 背景の設定
	m_spriteRender.SetMulColor(alpha);
	m_spriteRender.Update();
}

void Fade::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}