#include "stdafx.h"
#include "Guide.h"

#include "Title.h"
#include "UI/Fade.h"

namespace
{
	const float		FONT_SHADOW_OFFSET = 2.0f;							// �s�N�Z���̃I�t�Z�b�g��
	const Vector4	FONT_SHADOW_COLOR = { 1.0f,1.0f,1.0f,1.0f };		// �J���[
}

Guide::Guide()
{
}

Guide::~Guide()
{
}

bool Guide::Start()
{
	m_level2DRender = new Level2DRender;

	m_level2DRender->Init("Assets/level/level2D/guide.casl", [&](Level2DObjeData& objData) {
		if (objData.EqualObjectName("title") == true) {
			m_spriteRenderBackGround.Init(objData.ddsFilePath, objData.width, objData.height);
			m_spriteRenderBackGround.SetPosition(objData.position);
			m_spriteRenderBackGround.SetRotation(objData.rotation);
			m_spriteRenderBackGround.Update();
			return true;
		}
		if (objData.EqualObjectName("guide") == true) {
			m_spriteRenderGuide.Init(objData.ddsFilePath, objData.width, objData.height);
			m_spriteRenderGuide.SetPosition(objData.position);
			m_spriteRenderGuide.SetRotation(objData.rotation);
			m_spriteRenderGuide.Update();
			return true;
		}
		if (objData.EqualObjectName("image") == true) {
			m_spriteRenderGuideImage.Init(objData.ddsFilePath, objData.width, objData.height);
			m_spriteRenderGuideImage.SetPosition(objData.position);
			m_spriteRenderGuideImage.SetRotation(objData.rotation);
			m_spriteRenderGuideImage.Update();
			return true;
		}

		return false;
	});

	m_fontRender.SetText(L"Press A button to Title");
	m_fontRender.SetPosition({ -250.0f,-400.0f,0.0f });
	m_fontRender.SetColor({ 0.0f,0.0f,0.0f,1.0f });
	m_fontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

	//�t�F�[�h�C���B
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();

	return true;
}

void Guide::Update()
{
	if (m_isWaitFadeOut) {
		//�t�F�[�h���I�����Ă���Ȃ�B
		if (!m_fade->IsFade()) {
			m_title = NewGO<Title>(0, "title");
			DeleteGO(this);
		}
	}
	else {
		//A�{�^���������ꂽ��B
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_fade->FadeOut();
			m_isWaitFadeOut = true;
		}
	}
}

void Guide::Render(RenderContext& rc)
{
	// �`��
	m_spriteRenderBackGround.Draw(rc);
	m_spriteRenderGuideImage.Draw(rc);
	m_spriteRenderGuide.Draw(rc);
	m_fontRender.Draw(rc);
}