#include "stdafx.h"
#include "GameResult.h"

GameResult::GameResult()
{

}

GameResult::~GameResult()
{

}

bool GameResult::Start()
{
	m_spriteRender.Init("Asseets/Sprite/UI/Scene/result.DDS", 1920, 1080);
	m_spriteRender.SetPosition({ 0.0f, 0.0f, 0.0f });
	m_spriteRender.Update();

	return true;
}

void GameResult::Update()
{

}

void GameResult::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}