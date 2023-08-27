#include "stdafx.h"
#include "Fade.h"

namespace
{
	const float FADE_SPEED = 0.7f;		// �t�F�[�h�̑��x
	const float FONT_SCALE = 1.0f;		// �t�H���g�̃X�P�[��
	const float ROT_ANGLE = 2.0f;		// ��]�p�x
}

Fade::Fade()
{
}

Fade::~Fade()
{
}

bool Fade::Start()
{
	m_spriteRender.Init("Assets/sprite/UI/Scene/image.DDS", 1920.0f, 1080.0f, AlphaBlendMode_Multiply, 3);

	// �X�v���C�g�̐ݒ�
	m_imageSpriteRender.Init("Assets/Sprite/UI/Scene/image_nowloading.DDS", 149.0f, 141.0f);
	m_imageSpriteRender.SetScale(Vector3(0.4f, 0.4f, 0.4f));
	m_imageSpriteRender.SetPosition(Vector3(440.0f, -405.0f, 0.0f));

	// �e�L�X�g�̐ݒ�
	m_fontRender.SetText(L"Now Loading...");
	m_fontRender.SetColor(Vector4::White);
	m_fontRender.SetScale(FONT_SCALE);
	m_fontRender.SetPosition(Vector3(600.0f, -460.0f, 0.0f));

	return true;
}

void Fade::Update()
{
	switch (m_fadeState) {
	case m_enFadeState_FadeIn:
		// �����x�����炷
		m_alpha -= FADE_SPEED * g_gameTime->GetFrameDeltaTime();

		if (m_alpha < 0.0f) {
			m_alpha = 0.0f;						// �␳
			m_fadeState = m_enFadeState_Idle;	// �ҋ@��ԂɈڍs
		}
		break;
	case m_enFadeState_FadeOut:
		// �����x�𑝂₷
		m_alpha += FADE_SPEED * g_gameTime->GetFrameDeltaTime();

		if (m_alpha > 1.0f) {
			m_alpha = 1.0f;						// �␳
			m_fadeState = m_enFadeState_Idle;	// �ҋ@��ԂɈڍs
		}
		break;
	case m_enFadeState_Idle:
		break;
	}

	// �o�b�t�@�[�̒l�ɓ����x��n��
	RenderingEngine::GetInstance()->GetSpriteCB().fadeValue = m_alpha;

	if (!m_isDraw) {
		return;
	}

	RotationImage();
	m_fontRender.SetColor(Vector4(m_alpha, m_alpha, m_alpha, m_alpha));
}

void Fade::RotationImage()
{
	m_timer += g_gameTime->GetFrameDeltaTime();

	// ��]
	Quaternion rot = Quaternion::Identity;
	rot.AddRotationZ(ROT_ANGLE * m_timer);
	// �����x
	Vector4 alpha = Vector4(1.0f, 1.0f, 1.0f, m_alpha);


	m_imageSpriteRender.SetRotation(rot);
	m_imageSpriteRender.SetScale(Vector3(rot.x, rot.y, 1.0f));
	m_imageSpriteRender.SetMulColor(alpha);
	m_imageSpriteRender.Update();
}


void Fade::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);

	if (!m_isDraw) {
		return;
	}

	m_imageSpriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}