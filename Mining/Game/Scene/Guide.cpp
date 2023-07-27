#include "stdafx.h"
#include "Guide.h"

#include "Title.h"
#include "UI/Fade.h"

namespace
{
	const float		FONT_SHADOW_OFFSET = 2.0f;									// ピクセルのオフセット量
	const Vector3	FONT_POSITION = Vector3(-250.0f, -400.0f, 0.0f);			// フォントの座標
	const Vector4	FONT_SHADOW_COLOR = Vector4(1.0f, 1.0f, 1.0f, 1.0f);		// カラー
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

	m_fontRender.SetText(L"Aボタンでタイトルに戻る");
	m_fontRender.SetPosition(FONT_POSITION);
	m_fontRender.SetColor(Vector4::Black);
	m_fontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

	//フェードイン。
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();

	return true;
}

void Guide::Update()
{
	if (m_isWaitFadeOut) {
		//フェードが終了しているなら。
		if (!m_fade->IsFade()) {
			m_title = NewGO<Title>(0, "title");
			DeleteGO(this);
		}
	}
	else {
		//Aボタンが押されたら。
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_fade->FadeOut();
			m_isWaitFadeOut = true;
		}
	}
}

void Guide::Render(RenderContext& rc)
{
	// 描画
	m_spriteRenderBackGround.Draw(rc);
	m_spriteRenderGuideImage.Draw(rc);
	m_spriteRenderGuide.Draw(rc);
	m_fontRender.Draw(rc);
}