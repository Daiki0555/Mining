#include "stdafx.h"
#include "Title.h"

#include "Game.h"
#include "Ranking.h"
#include "UI/Fade.h"

namespace 
{
	const float		FONT_POSITION_X = -550.0f;							// 各項目のX座標

	const float		FONT_SHADOW_OFFSET = 2.0f;							// ピクセルのオフセット量
	const Vector4	FONT_SHADOW_COLOR = { 1.0f,1.0f,1.0f,1.0f };		// カラー
}

Title::Title()
{
}

Title::~Title()
{
}

bool Title::Start()
{
	m_level2DRender = new Level2DRender;

	m_level2DRender->Init("Assets/level/level2D/title.casl", [&](Level2DObjeData& objData) {
		if (objData.EqualObjectName("title") == true) {
			m_spriteRenderTitle.Init(objData.ddsFilePath, objData.width, objData.height);
			m_spriteRenderTitle.SetPosition(objData.position);
			m_spriteRenderTitle.SetRotation(objData.rotation);
			m_spriteRenderTitle.Update();
			return true;
		}
		if (objData.EqualObjectName("rogo") == true) {
			m_spriteRenderRogo.Init(objData.ddsFilePath, objData.width, objData.height);
			m_spriteRenderRogo.SetPosition(objData.position);
			m_spriteRenderRogo.SetRotation(objData.rotation);
			m_spriteRenderRogo.Update();
			return true;
		}

		return false;
	});

	m_spriteRenderIcon.Init("Assets/Sprite/UI/Scene/title/cursor.DDS", 89.0f, 94.0f);
	m_spriteRenderIcon.SetScale({ 0.7f, 0.7f, 1.0f });
	m_spriteRenderIcon.Update();

	//フェードイン。
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();

	return true;
}

void Title::Update()
{
	ChangeScene();
	TransparentProcess();

	switch (m_MessageState){
	case m_enMessageState_Start:

		m_StartMessage.SetText(L"Aボタンを押してください");
		m_StartMessage.SetPosition({ -680.0f,-150.0f,0.0f });
		m_StartMessage.SetColor({ 0.0f, 0.0f, 0.0f, m_alpha });
		m_StartMessage.SetShadowParam(true, FONT_SHADOW_OFFSET, { m_alpha,m_alpha,m_alpha,1.0f });

		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_MessageState = m_enMessageState_Select;
		}

		break;
	case m_enMessageState_Select:

		m_GameStartMessage.SetText(L"ゲームスタート");
		m_GameStartMessage.SetPosition({ FONT_POSITION_X,50.0f,0.0f });
		m_GameStartMessage.SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		m_GameStartMessage.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

		m_SystemMessage.SetText(L"操作説明");
		m_SystemMessage.SetPosition({ FONT_POSITION_X,-100.0f,0.0f });
		m_SystemMessage.SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		m_SystemMessage.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

		m_RankingMessage.SetText(L"ランキング");
		m_RankingMessage.SetPosition({ FONT_POSITION_X,-250.0f,0.0f });
		m_RankingMessage.SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		m_RankingMessage.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

		switch (m_CursorState) {
		case m_enCursorState_Game:
			m_GameStartMessage.SetColor({ m_alpha, 0.0f, 0.0f, m_alpha });
			m_GameStartMessage.SetShadowParam(true, FONT_SHADOW_OFFSET, { m_alpha,m_alpha,m_alpha,1.0f });

			m_spriteRenderIcon.SetPosition({ -500.0f, 20.0f, 0.0f });
			break;
		case m_enCursorState_Guide:
			m_SystemMessage.SetColor({ m_alpha, 0.0f, 0.0f, m_alpha });
			m_SystemMessage.SetShadowParam(true, FONT_SHADOW_OFFSET, { m_alpha,m_alpha,m_alpha,1.0f });

			m_spriteRenderIcon.SetPosition({ -500.0f,-100.0f,0.0f });
			break;
		case m_enCursorState_Ranking:
			m_RankingMessage.SetColor({ m_alpha, 0.0f, 0.0f, m_alpha });
			m_RankingMessage.SetShadowParam(true, FONT_SHADOW_OFFSET, { m_alpha,m_alpha,m_alpha,1.0f });

			m_spriteRenderIcon.SetPosition({ -500.0f,-220.0f,0.0f });
			break;
		}

		if (m_isWaitFadeOut) {
			//フェードが終了しているなら。
			if (!m_fade->IsFade()) {
				FadeScene();
			}
		}
		else {
			//Aボタンが押されたら。
			if (g_pad[0]->IsTrigger(enButtonA)) {
				m_fade->FadeOut();
				m_isWaitFadeOut = true;
			}
		}
		break;
	}

	m_spriteRenderIcon.Update();
}

void Title::TransparentProcess()
{
	if (m_isChange) {
		m_alpha += g_gameTime->GetFrameDeltaTime();

		if (m_alpha >= 1.0f) {
			m_alpha = 1.0f;
			m_isChange = false;
		}
	}
	else {
		m_alpha -= g_gameTime->GetFrameDeltaTime();

		if (m_alpha <= 0.0f) {
			m_alpha = 0.0f;
			m_isChange = true;
		}
	}
}

void Title::ChangeScene()
{
	if (g_pad[0]->IsTrigger(enButtonUp)) {
		switch (m_CursorState) {
		case m_enCursorState_Game:
			m_CursorState = m_enCursorState_Game;
			break;
		case m_enCursorState_Guide:
			m_CursorState = m_enCursorState_Game;
			break;
		case m_enCursorState_Ranking:
			m_CursorState = m_enCursorState_Guide;
			break;
		}
	}

	if (g_pad[0]->IsTrigger(enButtonDown)) {
		switch (m_CursorState) {
		case m_enCursorState_Game:
			m_CursorState = m_enCursorState_Guide;
			break;
		case m_enCursorState_Guide:
			m_CursorState = m_enCursorState_Ranking;
			break;
		case m_enCursorState_Ranking:
			m_CursorState = m_enCursorState_Ranking;
			break;
		}
	}
}

void Title::FadeScene()
{
	switch (m_CursorState) {
	case m_enCursorState_Game:
		m_game = NewGO<Game>(0, "game");
		DeleteGO(this);
		break;
	case m_enCursorState_Guide:
		break;
	case m_enCursorState_Ranking:
		m_ranking = NewGO<Ranking>(0, "ranking");
		DeleteGO(this);
		break;
	}
}

void Title::Render(RenderContext& rc)
{
	m_spriteRenderTitle.Draw(rc);
	m_spriteRenderRogo.Draw(rc);

	if (m_MessageState == m_enMessageState_Start) {
		m_StartMessage.Draw(rc);
	}
	else if (m_MessageState == m_enMessageState_Select) {
		m_spriteRenderIcon.Draw(rc);
		m_GameStartMessage.Draw(rc);
		m_RankingMessage.Draw(rc);
		m_SystemMessage.Draw(rc);
	}
}