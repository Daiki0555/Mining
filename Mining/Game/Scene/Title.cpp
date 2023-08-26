#include "stdafx.h"
#include "Title.h"

#include "Game.h"
#include "Ranking.h"
#include "UI/Fade.h"
#include "Guide.h"
#include "Sound.h"

namespace 
{
	const float		FONT_POSITION_X = -550.0f;							// �e���ڂ�X���W
	const float		FONT_SHADOW_OFFSET = 2.0f;							// �s�N�Z���̃I�t�Z�b�g��
	const Vector4	FONT_SHADOW_COLOR = Vector4(1.0f, 1.0f, 1.0f, 1.0f);// �J���[

	const float		UV_SCROLLSPEED = 0.00002f;							// UV�X�N���[���̃X�s�[�h
}

Title::Title()
{
}

Title::~Title()
{
}

bool Title::Start()
{
	m_level2DRender = new Level2DRender;

	m_level2DRender->Init("Assets/level/level2D/title.casl", [&](Level2DObjeData& objData) {
		if (objData.EqualObjectName("unityChan_mask") == true) {
			m_spriteRenderTitle.Init(objData.ddsFilePath, objData.width, objData.height);
			m_spriteRenderTitle.SetPosition(objData.position);
			m_spriteRenderTitle.SetRotation(objData.rotation);
			m_spriteRenderTitle.Update();
			return true;
		}
		if (objData.EqualObjectName("rogo") == true) {
			m_spriteRenderRogo.Init(objData.ddsFilePath, objData.width, objData.height);
			m_spriteRenderRogo.SetPosition(objData.position);
			m_spriteRenderRogo.SetRotation(objData.rotation);
			m_spriteRenderRogo.Update();
			return true;
		}
		if (objData.EqualObjectName("UV") == true) {
			m_spriteRenderUV.Init("Assets/Sprite/UI/Scene/title/UV.DDS", objData.width, objData.height, AlphaBlendMode_None, 2);
			m_spriteRenderUV.SetPosition(objData.position);
			m_spriteRenderUV.SetRotation(objData.rotation);
			m_spriteRenderUV.Update();
			return true;
		}

		return false;
	});

	// �J�[�\���摜�̐ݒ�
	m_spriteRenderIcon.Init("Assets/Sprite/UI/Scene/title/cursor.DDS", 89.0f, 94.0f);
	m_spriteRenderIcon.SetScale({ 0.7f, 0.7f, 1.0f });
	m_spriteRenderIcon.SetPosition({ -500.0f, 15.0f, 0.0f });
	m_spriteRenderIcon.Update();

	// UV�X�N���[���p�̒l��������
	m_uvTimer = UV_SCROLLSPEED;

	//�t�F�[�h�C���B
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();
	m_fade->SetDrawFlag(false);

	m_sound = FindGO<Sound>("sound");
	m_sound->SetSoundBGM(m_sound->m_enSoundState_TitleBGM);
	m_sound->SetStoPflag(true);

	return true;
}

void Title::Update()
{
	ChangeScene();
	TransparentProcess();

	// UV�X�N���[���̏���
	RenderingEngine::GetInstance()->GetSpriteCB().clipSize.x += m_uvTimer;

	switch (m_MessageState){
	case m_enMessageState_Start:

		// �����̐ݒ�
		m_StartMessage.SetText(L"B�{�^���������Ă�������");
		m_StartMessage.SetPosition({ -680.0f,-150.0f,0.0f });
		m_StartMessage.SetColor({ 0.0f, 0.0f, 0.0f, m_alpha });
		m_StartMessage.SetShadowParam(true, FONT_SHADOW_OFFSET, { m_alpha,m_alpha,m_alpha,1.0f });

		// B�{�^���������ꂽ�Ȃ�
		if (g_pad[0]->IsTrigger(enButtonB)) {
			m_sound->SetSoundSE(m_sound->m_enSoundState_FixedSE);
			// ���̃X�e�[�g�Ɉڍs����
			m_MessageState = m_enMessageState_Select;
		}
		break;
	case m_enMessageState_Select:

		// �Q�[���J�n�̕����̐ݒ�
		m_GameStartMessage.SetText(L"�Q�[���X�^�[�g");
		m_GameStartMessage.SetPosition({ FONT_POSITION_X,50.0f,0.0f });
		m_GameStartMessage.SetColor(Vector4::Black);
		m_GameStartMessage.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

		// ��������̕����̐ݒ�
		m_SystemMessage.SetText(L"�������");
		m_SystemMessage.SetPosition({ FONT_POSITION_X,-100.0f,0.0f });
		m_SystemMessage.SetColor(Vector4::Black);
		m_SystemMessage.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

		// �����L���O�̕����̐ݒ�
		m_RankingMessage.SetText(L"�����L���O");
		m_RankingMessage.SetPosition({ FONT_POSITION_X,-250.0f,0.0f });
		m_RankingMessage.SetColor(Vector4::Black);
		m_RankingMessage.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

		// �J�[�\���̈ʒu�ɉ����ē��ߏ������s��
		switch (m_CursorState) {
		case m_enCursorState_Game:
			m_GameStartMessage.SetColor({ m_alpha, 0.0f, 0.0f, m_alpha });
			m_GameStartMessage.SetShadowParam(true, FONT_SHADOW_OFFSET, { m_alpha,m_alpha,m_alpha,1.0f });

			m_spriteRenderIcon.SetPosition({ -500.0f, 15.0f, 0.0f });
			m_fade->SetDrawFlag(true);
			break;
		case m_enCursorState_Guide:
			m_SystemMessage.SetColor({ m_alpha, 0.0f, 0.0f, m_alpha });
			m_SystemMessage.SetShadowParam(true, FONT_SHADOW_OFFSET, { m_alpha,m_alpha,m_alpha,1.0f });

			m_spriteRenderIcon.SetPosition({ -500.0f,-110.0f,0.0f });
			m_fade->SetDrawFlag(false);
			break;
		case m_enCursorState_Ranking:
			m_RankingMessage.SetColor({ m_alpha, 0.0f, 0.0f, m_alpha });
			m_RankingMessage.SetShadowParam(true, FONT_SHADOW_OFFSET, { m_alpha,m_alpha,m_alpha,1.0f });

			m_spriteRenderIcon.SetPosition({ -500.0f,-230.0f,0.0f });
			m_fade->SetDrawFlag(false);
			break;
		}

		if (m_isWaitFadeOut) {
			//�t�F�[�h���I�����Ă���Ȃ�B
			if (!m_fade->IsFade()) {
				FadeScene();
			}
		}
		else {
			// B�{�^���������ꂽ��B
			if (g_pad[0]->IsTrigger(enButtonB)) {
				m_sound->SetSoundSE(m_sound->m_enSoundState_FixedSE);
				m_fade->FadeOut();
				m_isWaitFadeOut = true;
				// BGM���폜����
				m_sound->DeleteBGM();
			}
			// A�{�^���������ꂽ�Ȃ�
			if (g_pad[0]->IsTrigger(enButtonA)) {
				m_sound->SetSoundSE(m_sound->m_enSoundState_CancelSE);
				// �O�̃X�e�[�g�Ɉڍs����
				m_MessageState = m_enMessageState_Start;
			}
		}
		break;
	}

	m_spriteRenderIcon.Update();
}

void Title::TransparentProcess()
{
	if (m_isChange) {
		m_alpha += g_gameTime->GetFrameDeltaTime();

		if (m_alpha >= 1.0f) {
			m_alpha = 1.0f;
			m_isChange = false;
		}
	}
	else {
		m_alpha -= g_gameTime->GetFrameDeltaTime();

		if (m_alpha <= 0.0f) {
			m_alpha = 0.0f;
			m_isChange = true;
		}
	}
}

void Title::ChangeScene()
{
	if (g_pad[0]->IsTrigger(enButtonUp)) {
		switch (m_CursorState) {
		case m_enCursorState_Game:
			m_CursorState = m_enCursorState_Game;
			break;
		case m_enCursorState_Guide:
			m_CursorState = m_enCursorState_Game;
			break;
		case m_enCursorState_Ranking:
			m_CursorState = m_enCursorState_Guide;
			break;
		}
	}

	if (g_pad[0]->IsTrigger(enButtonDown)) {
		switch (m_CursorState) {
		case m_enCursorState_Game:
			m_CursorState = m_enCursorState_Guide;
			break;
		case m_enCursorState_Guide:
			m_CursorState = m_enCursorState_Ranking;
			break;
		case m_enCursorState_Ranking:
			m_CursorState = m_enCursorState_Ranking;
			break;
		}
	}
}

void Title::FadeScene()
{
	// �X�e�[�g�ɉ����Đ�������V�[����؂�ւ���
	switch (m_CursorState) {
	case m_enCursorState_Game:
		m_game = NewGO<Game>(0, "game");
		// BGM���폜����
		m_sound->DeleteBGM();
		m_sound->SetStoPflag(false);
		DeleteGO(this);
		break;
	case m_enCursorState_Guide:
		m_guide = NewGO<Guide>(0, "guide");
		DeleteGO(this);
		break;
	case m_enCursorState_Ranking:
		m_ranking = NewGO<Ranking>(0, "ranking");
		DeleteGO(this);
		break;
	}
}

void Title::Render(RenderContext& rc)
{
	m_spriteRenderUV.Draw(rc);
	m_spriteRenderTitle.Draw(rc);
	m_spriteRenderRogo.Draw(rc);

	if (m_MessageState == m_enMessageState_Start) {
		m_StartMessage.Draw(rc);
	}
	else if (m_MessageState == m_enMessageState_Select) {
		m_spriteRenderIcon.Draw(rc);
		m_GameStartMessage.Draw(rc);
		m_RankingMessage.Draw(rc);
		m_SystemMessage.Draw(rc);
	}
}