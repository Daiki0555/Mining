#include "stdafx.h"
#include "Crystal.h"
#include "Player.h"

namespace
{
	const float SCALE = 5.0f;
}

Crystal::Crystal()
{
}

Crystal::~Crystal()
{
}

bool Crystal::Start()
{
	// クリスタルのモデル
	m_modelRenderCrystal.Init("Assets/modelData/stage/Crystal/Crystal.tkm");
	m_modelRenderCrystal.SetPosition(m_position);
	m_modelRenderCrystal.SetScale(m_scale);
	m_modelRenderCrystal.SetRotaition(m_rotation);
	m_modelRenderCrystal.Update();

	// 岩のモデル
	m_modelRenderRock.Init("Assets/modelData/stage/Crystal/Crystal_Rock.tkm");
	m_modelRenderRock.SetPosition(m_position);
	m_modelRenderRock.SetScale(m_scale);
	m_modelRenderRock.SetRotaition(m_rotation);
	m_modelRenderRock.Update();

	// テクスチャを変更
	m_modelRenderCrystal.GetModel().ChangeAlbedoMap("", m_texture);

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
	m_modelRenderCrystal.Draw(rc);
	m_modelRenderRock.Draw(rc);
}

