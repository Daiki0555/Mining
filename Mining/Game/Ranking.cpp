#include "stdafx.h"
#include "Ranking.h"

#include "SaveDataManager.h"
#include "Scene/Title.h"

namespace
{
	const Vector3	BUTTON_FONT_POS = Vector3(-500.0f, -400.0f, 0.0f);		//�{�^�������̍��W�B
	const Vector3	RANKNIG_FONT_POS = Vector3(-300.0f, 200.0f, 0.0f);		//�����L���O�����̍��W�B
	const Vector3	RANKING_BETWEEN_ROW = Vector3(0.0f, -50.0f, 0.0f);		//�����L���O�����̗�ԁB
	const int		RANKING_NUM = 10;										//�����L���O�̏��ʁB
	const int		NAME_MAX = 5;											//���O�̍ő���͐��B
	const char*		RANK[RANKING_NUM] = { " 1st", " 2nd", " 3rd", " 4th", " 5th", " 6th", " 7th", " 8th", " 9th", "10th" };
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
	m_backGroundSpriteRender.Init("Assets/Sprite/UI/Scene/ranking.DDS", 1920.0f, 1080.0f);

	//�{�^�������̐ݒ�B
	m_buttonFontRender.SetText(L"Press A button to Title");
	m_buttonFontRender.SetPosition(BUTTON_FONT_POS);
	m_buttonFontRender.SetScale(2.0f);
	m_buttonFontRender.SetColor(Vector4::Black);

	InitRanking();

	return true;
}

void Ranking::InitRanking()
{
	SaveDataManager saveDataMng;
	SaveDataManager::SaveData data;
	char name[BUFFER_SIZE];

	//�������ƃ��[�h�B
	saveDataMng.Init(data);
	//saveDataMng.Save(data);
	saveDataMng.Load(data);

	//�t�@�C����ǂݍ��ށB
	FILE* fp = fopen("rankingName.txt", "r");
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
	}
}

void Ranking::Update()
{
	//A�{�^���������ꂽ��B
	if (g_pad[0]->IsTrigger(enButtonA)) {

		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}

void Ranking::Render(RenderContext& rc)
{
	//�w�i�摜�̕`��B
	m_backGroundSpriteRender.Draw(rc);

	//�����L���O�����̕`��B
	for (int i = 0; i < RANKING_NUM; i++) {
		m_rankingFontRender[i].Draw(rc);
	}

	//�{�^�������̕`��B
	m_buttonFontRender.Draw(rc);
}