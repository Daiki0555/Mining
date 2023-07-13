#include "stdafx.h"
#include "Title.h"

#include "Game.h"
#include "Ranking.h"
#include "UI/Fade.h"

namespace 
{
}

Title::Title()
{
}

Title::~Title()
{
}

bool Title::Start()
{
	m_spriteRenderTitle.Init("Assets/Sprite/UI/Scene/title.DDS", 1920.0f, 1080.0f);
	m_spriteRenderTitle.SetPosition({ 0.0f,0.0f,0.0f });
	m_spriteRenderTitle.SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRenderTitle.Update();

	m_StartMessage.SetText(L"Aボタンを押してください");
	m_StartMessage.SetPosition({ 0.0f,-150.0f,0.0f });

	m_GameStartMessage.SetText(L"ゲームスタート");
	m_RankingMessage.SetText(L"ランキング");
	m_SystemMessage.SetText(L"操作説明");

	//フェードイン。
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();

	return true;
}

void Title::Update()
{
	ChangeScene();

	switch (m_MessageState){
	m_enMessageState_Start:
		TransparentProcess();

		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_MessageState = m_enMessageState_Select;
		}

		break;
	m_enMessageState_Select:
		ChangeCursor();
		break;
	}
}

void Title::TransparentProcess()
{
	m_alpha -= g_gameTime->GetFrameDeltaTime();

	if (m_alpha <= 0.0f) {
		m_alpha = 1.0f;
	}

	m_StartMessage.SetColor({ 0.0f, 0.0f, 0.0f, m_alpha });
}

void Title::ChangeScene()
{
	if (g_pad[0]->IsTrigger(enButtonUp)) {
		
		if (m_enCursorState_Game) {
			m_CursorState = m_enCursorState_Game;
			return;
		}
		else if (m_enCursorState_Guide) {
			m_CursorState = m_enCursorState_Game;
			return;
		}
		m_CursorState = m_enCursorState_Guide;
		return;
	}

	if (g_pad[0]->IsTrigger(enButtonDown)) {

		if (m_enCursorState_Game) {
			m_CursorState = m_enCursorState_Guide;
			return;
		}
		else if (m_enCursorState_Guide) {
			m_CursorState = m_enCursorState_Ranking;
			return;
		}
		m_CursorState = m_enCursorState_Ranking;
		return;
	}
}

void Title::ChangeCursor()
{
	switch (m_CursorState) {
	case m_enCursorState_Game:

		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_game = NewGO<Game>(0, "game");
			DeleteGO(this);
		}

		break;
	case m_enCursorState_Guide:
		break;
	case m_enCursorState_Ranking:

		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_ranking = NewGO<Ranking>(0, "ranking");
			DeleteGO(this);
		}

		break;
	}
}

void Title::Render(RenderContext& rc)
{
	m_spriteRenderTitle.Draw(rc);

	if (m_MessageState == m_enMessageState_Start) {
		m_StartMessage.Draw(rc);
	}
	else if (m_MessageState == m_enMessageState_Select) {
		m_GameStartMessage.Draw(rc);
		m_RankingMessage.Draw(rc);
		m_SystemMessage.Draw(rc);
	}
}