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
	
}

void Title::Update()
{
	// ˆê’è‚Ìƒ{ƒ^ƒ“‚ğ‰Ÿ‚µ‚½‚Æ‚«
	if (g_pad[0]->IsTrigger(enButtonA)) {
		// ƒQ[ƒ€‚ğ¶¬
		m_game = NewGO<Game>(0, "game");
		DeleteGO(this);
	}
}

void Title::Transparent()
{
	// •¶š‚ğ“§‰ß‚·‚é
}

void Title::Render(RenderContext& rc)
{

}