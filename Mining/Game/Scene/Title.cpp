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
	// ���̃{�^�����������Ƃ�
	if (g_pad[0]->IsTrigger(enButtonA)) {
		// �Q�[���𐶐�
		m_game = NewGO<Game>(0, "game");
		DeleteGO(this);
	}
}

void Title::Transparent()
{
	// �����𓧉߂���
}

void Title::Render(RenderContext& rc)
{

}