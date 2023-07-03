#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{

}

Title::~Title()
{

}

bool Title::Start()
{
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
}

void Title::Transparent()
{
	// 文字を透過する
}

void Title::Render(RenderContext& rc)
{

}