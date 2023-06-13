#include "stdafx.h"
#include "Debug.h"
Debug::Debug()
{
	//�A�j���[�V������ǂݍ���
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

	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%d�b�o��!!", int(m_timer));

	//�\������e�L�X�g��ݒ�B
	m_fontRender.SetText(wcsbuf);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender.SetPosition(Vector3(200.0f, 200.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender.SetScale(2.0f);
	//�t�H���g�̐F��ݒ�B
	m_fontRender.SetColor({ 1.0f,0.0f,0.0f,1.0f });
	m_fontRender.SetShadowParam(true, 2.0f, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_timer += g_gameTime->GetFrameDeltaTime();
	
	
	m_modelRender.PlayAnimation(m_enAnimationClip_Idle, 0.5f);
	m_modelRender.Update();
	m_spriteRender.Update();
}

void Debug::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	//m_spriteRender.Draw(rc);
	//m_fontRender.Draw(rc);
}