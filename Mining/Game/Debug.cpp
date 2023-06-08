#include "stdafx.h"
#include "Debug.h"
Debug::Debug()
{
	//アニメーションを読み込む
	m_animationClips[m_enAnimationClip_Idle].Load("Assets/animData/player/idle.tka");
	m_animationClips[m_enAnimationClip_Idle].SetLoopFlag(true);
	m_modelRender.Init("Assets/modelData/player/unityChan.tkm",m_animationClips, m_enAnimationClip_Num, enModelUpAxisY);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotaition(m_rotaition);
	m_spriteRender.Init("Assets/Sprite/stamina.DDS", 500, 500);
	m_spriteRender.SetPosition(Vector3::Zero);
	m_spriteRender.SetScale(Vector3::One);
	m_spriteRender.Update();
}
Debug::~Debug()
{

}
void Debug::Update()
{
	m_modelRender.PlayAnimation(m_enAnimationClip_Idle, 0.5f);
	m_modelRender.Update();
	m_spriteRender.Update();
}

void Debug::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	m_spriteRender.Draw(rc);
}