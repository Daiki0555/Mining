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
	m_modelRender.Init("Assets/modelData/stage/stage.tkm", 0, 0, enModelUpAxisZ, false, true);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotaition(m_rotaion);
	m_modelRender.Update();

	m_physicsStaticObjct.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_physicsStaticObjct.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Wall);

	return true;
}

void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}