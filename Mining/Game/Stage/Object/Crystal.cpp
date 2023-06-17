#include "stdafx.h"
#include "Crystal.h"
#include "Player.h"

Crystal::Crystal()
{
}

Crystal::~Crystal()
{
}

bool Crystal::Start()
{
	m_modelRender.Init("Assets/modelData/stage/Crystal/Crystal.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotaition(m_rotation);
	m_modelRender.Update();

	m_modelRender.GetModel().ChangeAlbedoMap("", m_texture);

	return true;
}

void Crystal::Update()
{
	GetCrystal();
}

void Crystal::GetCrystal()
{

}

void Crystal::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
