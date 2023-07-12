#include "stdafx.h"
#include "GameResult.h"

#include "Title.h"

namespace
{

}

GameResult::GameResult()
{

}

GameResult::~GameResult()
{

}

bool GameResult::Start()
{
	m_spriteRender.Init("Assets/Sprite/UI/Scene/result.DDS", 1920.0f, 1080.0f);
	m_spriteRender.SetPosition({ 0.0f, 0.0f, 0.0f });
	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.Update();

	return true;
}

void GameResult::Update()
{
	DrawScore();

	if (g_pad[0]->IsTrigger(enButtonA)) {
		// ƒ^ƒCƒgƒ‹‚Ö–ß‚é
		m_title = NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}

void GameResult::DrawScore()
{

}

void GameResult::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}