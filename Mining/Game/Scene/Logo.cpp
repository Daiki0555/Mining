#include "stdafx.h"
#include "Logo.h"

#include "UI/Fade.h"
#include "Title.h"

namespace
{
	const float		FADE_TIMER = 3.0f;											// フェードするまでの時間
	const float		FONT_SHADOW_OFFSET = 2.0f;									// ピクセルのオフセット量
	const Vector3	FONT_POSITION = Vector3(-110.0f, 100.0f, 0.0f);				// ピクセルの座標
	const Vector4	FONT_SHADOW_COLOR = Vector4(1.0f, 1.0f, 1.0f, 1.0f);		// ピクセルのオフセットのカラー
}

Logo::Logo()
{
}

Logo::~Logo()
{
}

bool Logo::Start()
{
	m_level2DRender = new Level2DRender;

	m_level2DRender->Init("Assets/level/level2D/logo.casl", [&](Level2DObjeData& objData) {
		if (objData.EqualObjectName("fade") == true) {
			m_spriteRenderBackGround.Init(objData.ddsFilePath, 1920.0f, 1080.0f);
			m_spriteRenderBackGround.SetPosition(objData.position);
			m_spriteRenderBackGround.SetRotation(objData.rotation);
			m_spriteRenderBackGround.Update();
			return true;
		}
		if (objData.EqualObjectName("image_logo") == true) {
			m_spriteRenderLogo.Init(objData.ddsFilePath, objData.width, objData.height);
			m_spriteRenderLogo.SetPosition(objData.position);
			m_spriteRenderLogo.SetRotation(objData.rotation);
			m_spriteRenderLogo.Update();
			return true;
		}

		return false;
	});

	m_fontRender.SetText(L"Created by");
	m_fontRender.SetColor(Vector4::Black);
	m_fontRender.SetPosition(FONT_POSITION);
	m_fontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

	//フェードイン。
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();

	return true;
}

void Logo::Update()
{
	if (m_isWaitFadeOut) {
		//フェードが終了しているなら。
		if (!m_fade->IsFade()) {
			m_title = NewGO<Title>(0, "title");
			DeleteGO(this);
		}
	}
	else {
		m_timer += g_gameTime->GetFrameDeltaTime();

		//Aボタンが押されたら。
		if (m_timer >= FADE_TIMER) {
			m_fade->FadeOut();
			m_isWaitFadeOut = true;
		}
	}
}

void Logo::Render(RenderContext& rc)
{
	m_spriteRenderBackGround.Draw(rc);
	m_spriteRenderLogo.Draw(rc);
	m_fontRender.Draw(rc);
}
