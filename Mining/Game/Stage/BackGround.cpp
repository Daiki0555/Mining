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
	// ���f���̓ǂݍ���
	m_modelRender.Init("Assets/modelData/stage/stage.tkm");
	m_physicsStaticObjct.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	return true;
}

void BackGround::Render(RenderContext& rc)
{
	// �`��
	m_modelRender.Draw(rc);
}