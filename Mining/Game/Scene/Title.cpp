#include "stdafx.h"
#include "Title.h"

#include "Game.h"
#include "Ranking.h"
#include "UI/Fade.h"

namespace 
{
	const Vector3	TEX_POSITION = { -150.0f,-200.0f,0.0f };		// 座標
	const Vector3	TEX_SCALE = { 0.5f,0.5f,0.5f };					// スケール

	const float		ALPHA_VALUE = 0.01f;							// α値
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

	m_spriteRenderMessage.Init("Assets/Sprite/UI/Button/StartMessage.DDS", 716.0f, 59.0f);
	m_spriteRenderMessage.SetPosition(TEX_POSITION);
	m_spriteRenderMessage.SetScale(TEX_SCALE);
	m_spriteRenderMessage.Update();

	//フェードイン。
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();

	return true;
}

void Title::Update()
{
	ChangeScene();
	ChangeCursor();

	m_spriteRenderMessage.Update();
}

void Title::ChangeScene()
{
	if (g_pad[0]->IsTrigger(enButtonUp)) {
		
		if (m_enCursorState_Game) {
			m_enCursorState = m_enCursorState_Game;
			return;
		}
		else if (m_enCursorState_Guide) {
			m_enCursorState = m_enCursorState_Game;
			return;
		}
		m_enCursorState = m_enCursorState_Guide;
		return;
	}

	if (g_pad[0]->IsTrigger(enButtonDown)) {

		if (m_enCursorState_Game) {
			m_enCursorState = m_enCursorState_Guide;
			return;
		}
		else if (m_enCursorState_Guide) {
			m_enCursorState = m_enCursorState_Ranking;
			return;
		}
		m_enCursorState = m_enCursorState_Ranking;
		return;
	}
}

void Title::ChangeCursor()
{
	switch (m_enCursorState) {
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
	m_spriteRenderMessage.Draw(rc);
}