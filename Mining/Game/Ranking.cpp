#include "stdafx.h"
#include "Ranking.h"

#include "SaveDataManager.h"
#include "Scene/Title.h"
#include "UI/Fade.h"

namespace
{
	const Vector3	BUTTON_FONT_POS = Vector3(-250.0f, -450.0f, 0.0f);		//�{�^�������̍��W�B
	const Vector3	RANKNIG_FONT_POS = Vector3(-400.0f, 150.0f, 0.0f);		//�����L���O�����̍��W�B
	const Vector3	RANKING_BETWEEN_ROW = Vector3(0.0f, -50.0f, 0.0f);		//�����L���O�����̗�ԁB
	const int		RANKING_NUM = 10;										//�����L���O�̏��ʁB
	const int		NAME_MAX = 5;											//���O�̍ő���͐��B
	const char*		RANK[RANKING_NUM] = { " 1st", " 2nd", " 3rd", " 4th", " 5th", " 6th", " 7th", " 8th", " 9th", "10th" };

	const float		FONT_SHADOW_OFFSET = 2.0f;								// �s�N�Z���̃I�t�Z�b�g��
	const Vector4	FONT_SHADOW_COLOR = { 1.0f,1.0f,1.0f,1.0f };			// �J���[
}

Ranking::Ranking()
{

}

Ranking::~Ranking()
{

}

bool Ranking::Start()
{
	//�w�i�摜�̐ݒ�B
	//m_backGroundSpriteRender.Init("Assets/Sprite/UI/Scene/ranking.DDS", 1920.0f, 1080.0f);

	//�{�^�������̐ݒ�B
	m_buttonFontRender.SetText(L"A�{�^���Ń^�C�g���ɖ߂�");
	m_buttonFontRender.SetPosition(BUTTON_FONT_POS);
	m_buttonFontRender.SetScale(1.0f);
	m_buttonFontRender.SetColor(Vector4::Black);
	m_buttonFontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

	m_level2DRender = new Level2DRender;

	m_level2DRender->Init("Assets/level/level2D/ranking.casl", [&](Level2DObjeData& objData) {
		if (objData.EqualObjectName("title") == true) {
			m_backGroundSpriteRender.Init(objData.ddsFilePath, objData.width, objData.height);
			m_backGroundSpriteRender.SetPosition(objData.position);
			m_backGroundSpriteRender.SetRotation(objData.rotation);
			m_backGroundSpriteRender.Update();
			return true;
		}
		if (objData.EqualObjectName("ranking") == true) {
			m_rankingSpriteRender.Init(objData.ddsFilePath, objData.width, objData.height);
			m_rankingSpriteRender.SetPosition(objData.position);
			m_rankingSpriteRender.SetRotation(objData.rotation);
			m_rankingSpriteRender.Update();
			return true;
		}
		if (objData.EqualObjectName("scoreRanking") == true) {
			m_rankingScoresSpriteRender.Init(objData.ddsFilePath, objData.width, objData.height);
			m_rankingScoresSpriteRender.SetPosition(objData.position);
			m_rankingScoresSpriteRender.SetRotation(objData.rotation);
			m_rankingScoresSpriteRender.Update();
		}

		return false;
		});

	InitRanking();

	//�t�F�[�h�C���B
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();

	return true;
}

void Ranking::InitRanking()
{
	SaveDataManager saveDataMng;
	SaveDataManager::SaveData data;
	char name[BUFFER_SIZE];

	//�������ƃ��[�h�B
	saveDataMng.Init(data);
	saveDataMng.Load(data);

	//�t�@�C����ǂݍ��ށB
	FILE* fp = fopen("rankingName.dat", "rb");
	if (fp != NULL) {
		fread(name, sizeof(name), 1, fp);
		fgets(name, BUFFER_SIZE, fp);
		name[BUFFER_SIZE - 1] = '\0';
		fclose(fp);
	}

	for (int i = 0; i < RANKING_NUM; i++) {

		int rank = NAME_MAX * i;

		//�����L���O�����̐ݒ�B
		wchar_t text[BUFFER_SIZE];
		swprintf_s(text, BUFFER_SIZE, L"%hs :     %05d pts        [ %c%c%c%c%c ]",
			RANK[i], data.score[i], name[rank], name[rank + 1], name[rank + 2], name[rank + 3], name[rank + 4]);
		m_rankingFontRender[i].SetText(text);
		m_rankingFontRender[i].SetPosition(Vector3(RANKNIG_FONT_POS + (RANKING_BETWEEN_ROW * i)));
		m_rankingFontRender[i].SetColor(Vector4::Black);
		m_rankingFontRender[i].SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);
	}
}

void Ranking::Update()
{
	//�t�F�[�h�A�E�g���Ȃ�B
	if (m_isWaitFadeOut) {

		//�t�F�[�h���I�����Ă���Ȃ�B
		if (!m_fade->IsFade()) {
			m_title = NewGO<Title>(0, "title");
			// �J�[�\���ʒu��ݒ肷��
			m_title->SetCursorScene(m_title->m_enCursorState_Ranking);
			DeleteGO(this);
		}
	}
	else {
		//A�{�^���������ꂽ��B
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_fade->FadeOut();
			m_isWaitFadeOut = true;
		}
	}
}

void Ranking::Render(RenderContext& rc)
{
	//�w�i�摜�̕`��B
	m_backGroundSpriteRender.Draw(rc);
	m_rankingSpriteRender.Draw(rc);
	m_rankingScoresSpriteRender.Draw(rc);

	//�����L���O�����̕`��B
	for (int i = 0; i < RANKING_NUM; i++) {
		m_rankingFontRender[i].Draw(rc);
	}

	//�{�^�������̕`��B
	m_buttonFontRender.Draw(rc);
}