#include "stdafx.h"
#include "Title.h"

#include "Game.h"
#include "ScoreRanking.h"

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

	return true;
}

void Title::Update()
{
	// 一定のボタンを押したとき
	if (g_pad[0]->IsTrigger(enButtonA)) {
		// ゲームを生成
		m_game = NewGO<Game>(0, "game");
		DeleteGO(this);
	}

	//SceneChange();
	//Transparent();

	m_spriteRenderMessage.Update();
}

void Title::SceneChange()
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

void Title::Transparent()
{
}

void Title::Render(RenderContext& rc)
{
	m_spriteRenderTitle.Draw(rc);
	m_spriteRenderMessage.Draw(rc);
}