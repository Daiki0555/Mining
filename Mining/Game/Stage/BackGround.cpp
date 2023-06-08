#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

bool BackGround::Start()
{
	// ƒ‚ƒfƒ‹‚Ì“Ç‚İ‚İ
	m_modelRender.Init("Assets/modelData/stage/stage.tkm");

	return true;
}

void BackGround::Render(RenderContext& rc)
{
	// •`‰æ
	m_modelRender.Draw(rc);
}