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
		// �����x�����炷
		m_alpha -= 1.0f * g_gameTime->GetFrameDeltaTime();

		if (m_alpha < 0.0f) {
			m_alpha = 0.0f;						// �␳
			m_fadeState = m_enFadeState_Idle;	// �ҋ@��ԂɈڍs
		}
		break;
	case m_enFadeState_FadeOut:
		// �����x�𑝂₷
		m_alpha += 1.0f * g_gameTime->GetFrameDeltaTime();

		if (m_alpha > 1.0f) {
			m_alpha = 1.0f;						// �␳
			m_fadeState = m_enFadeState_Idle;	// �ҋ@��ԂɈڍs
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

	// �w�i�̐ݒ�
	m_spriteRender.SetMulColor(alpha);
	m_spriteRender.Update();
}

void Fade::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}