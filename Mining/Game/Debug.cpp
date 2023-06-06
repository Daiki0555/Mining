#include "stdafx.h"
#include "Debug.h"
Debug::Debug()
{
	//アニメーションを読み込む
	m_animationClips[m_enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[m_enAnimationClip_Idle].SetLoopFlag(true);
	m_modelRender.Init("Assets/modelData/unityChan.tkm",m_animationClips, m_enAnimationClip_Num, enModelUpAxisY);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotaition(m_rotaition);
}
Debug::~Debug()
{

}
void Debug::Update()
{
	m_modelRender.PlayAnimation(m_enAnimationClip_Idle, 0.5f);
	m_modelRender.Update();
}

void Debug::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}