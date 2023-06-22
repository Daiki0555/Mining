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
	m_scale *= 1.5f;

	// ƒ‚ƒfƒ‹‚Ì“Ç‚Ýž‚Ý
	m_modelRender.Init("Assets/modelData/stage/stage.tkm");
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
	// •`‰æ
	m_modelRender.Draw(rc);
}