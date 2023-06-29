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
	m_modelRenderCrystal.Init("Assets/modelData/stage/Crystal/Crystal.tkm", 0, 0, enModelUpAxisZ, true);
	m_modelRenderCrystal.SetPosition(m_position);
	m_modelRenderCrystal.SetScale(m_scale);
	m_modelRenderCrystal.SetRotaition(m_rotation);
	m_modelRenderCrystal.Update();

	// 岩のモデル
	m_modelRenderRock.Init("Assets/modelData/stage/Crystal/Crystal_Rock.tkm", 0, 0, enModelUpAxisZ, true);
	m_modelRenderRock.SetPosition(m_position);
	m_modelRenderRock.SetScale(m_scale);
	m_modelRenderRock.SetRotaition(m_rotation);
	m_modelRenderRock.Update();

	// テクスチャを変更
	m_modelRenderCrystal.GetModel().ChangeAlbedoMap("", m_texture);

	// 当たり判定を作成
	m_physicsStaticObjct.CreateFromModel(m_modelRenderRock.GetModel(), m_modelRenderRock.GetModel().GetWorldMatrix(), 0.0f);
	m_physicsStaticObjct.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Crystal);

	return true;
}

void Crystal::GetCrystal()
{
	m_canDrawFlag = false;
}

void Crystal::Render(RenderContext& rc)
{
	// 自身が獲得されていないときは描画する
	if (m_canDrawFlag) {
		m_modelRenderCrystal.Draw(rc);
	}

	m_modelRenderRock.Draw(rc);
}