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
	// モデルの読み込み
	m_modelRender.Init("Assets/modelData/stage/stage.tkm");

	return true;
}

void BackGround::Render(RenderContext& rc)
{
	// 描画
	m_modelRender.Draw(rc);
}