#include "stdafx.h"
#include "GameResult.h"

#include "SaveDataManager.h"
#include "NameEntry.h"
#include "Title.h"
#include "UI/Fade.h"

namespace
{
	const Vector3	CRYSTAL_FONT_POS = Vector3(-50.0f, 320.0f, 0.0f);					//�N���X�^���������̍��W�B
	const Vector3	NEWRECORD_FONT_POS = Vector3(-175.0f, -250.0f, 0.0f);				//�V�L�^�����̍��W�B
	const int		CRYSTAL_POINTS[CRYSTAL_CATEGORY_MAX] = { 10, 100, 1000, 10000 };	//�N���X�^���̃|�C���g�B
	const float		CRYSTAL_FONT_SCALE = 1.3f;											//�N���X�^���������̊g�嗦�B
	const float		NEWRECORD_TIMER_MAX = 1.0f;											//�V�L�^�p�^�C�}�[�̍ő�l�B
	const float		NEWRECORD_TIMER_MIN = 0.0f;											//�V�L�^�p�^�C�}�[�̍ŏ��l�B
}

GameResult::GameResult()
{

}

GameResult::~GameResult()
{

}

bool GameResult::Start()
{
	CalcScore();

	//�w�i�摜�̐ݒ�B
	m_backGroundSpriteRender.Init("Assets/Sprite/UI/Scene/result.DDS", 1920.0f, 1080.0f);

	//�z�Ό������̐ݒ�B
	wchar_t text[BUFFER_SIZE];
	swprintf_s(text, BUFFER_SIZE, L"%02d \n\n%02d \n\n%02d \n\n%02d \n\n\n%d",
				m_haveCristals[0], m_haveCristals[1], m_haveCristals[2], m_haveCristals[3], m_newScore);
	m_crystalFontRender.SetText(text);
	m_crystalFontRender.SetPosition(CRYSTAL_FONT_POS);
	m_crystalFontRender.SetScale(CRYSTAL_FONT_SCALE);
	m_crystalFontRender.SetColor(Vector4::Black);

	//�V�L�^�����̐ݒ�B
	m_newRecordFontRender.SetText(L"NEW  RECORD!!!");
	m_newRecordFontRender.SetPosition(NEWRECORD_FONT_POS);
	m_newRecordFontRender.SetColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));

	//�t�F�[�h�C���B
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();

	return true;
}

void GameResult::CalcScore()
{
	//�X�R�A���v�Z�B
	for (int i = 0; i < CRYSTAL_CATEGORY_MAX; i++) {

		m_newScore += CRYSTAL_POINTS[i] * m_haveCristals[i];
	}

	//�Z�[�u�f�[�^��ǂݍ���Ńn�C�X�R�A���ǂ����m�F�B
	SaveDataManager saveDataMng;
	SaveDataManager::SaveData data;
	saveDataMng.Load(data);

	//�X�R�A�������L���O�̃X�R�A����Ȃ�B
	if (m_newScore > data.score[9]) {
		m_isNewRecord = true;
	}
}

void GameResult::Update()
{
	if (m_isWaitFadeOut) {

		//�t�F�[�h���I�����Ă���Ȃ�B
		if (!m_fade->IsFade()) {
			TransitionScene();
		}
	}
	else {
		//A�{�^���������ꂽ��B
		if (g_pad[0]->IsTrigger(enButtonA)) {
			m_fade->FadeOut();
			m_isWaitFadeOut = true;
		}
	}

	DrawScore();
}

void GameResult::DrawScore()
{
	//�V�L�^���̕�����ǉ��B
	if (m_isNewRecord) {

		m_newRecordTimer += g_gameTime->GetFrameDeltaTime();

		if (m_newRecordTimer > NEWRECORD_TIMER_MAX) {
			m_newRecordTimer = NEWRECORD_TIMER_MIN;
		}

		// (-t^2 + 2t) - 1
		float alpha = fabsf(pow(m_newRecordTimer, 2.0f) + (2.0f * m_newRecordTimer) - 1.0f);
		alpha = min( max( alpha, NEWRECORD_TIMER_MIN), NEWRECORD_TIMER_MAX);

		//�����x��ݒ�B
		m_newRecordFontRender.SetColor(Vector4(1.0f, 0.0f, 0.0f, alpha));
	}
}

void GameResult::TransitionScene()
{
	//�X�R�A�������L���O�̃X�R�A����Ȃ�B
	if (m_isNewRecord) {
		//�l�[���G���g���[�֑J�ځB
		NameEntry* nameEntry = NewGO<NameEntry>(0, "nameEntry");
		nameEntry->SetScore(m_newScore);
	}
	else {
		//�^�C�g���֑J�ځB
		NewGO<Title>(0, "title");
	}

	DeleteGO(this);
}

void GameResult::Render(RenderContext& rc)
{
	m_backGroundSpriteRender.Draw(rc);

	m_crystalFontRender.Draw(rc);

	if (m_isNewRecord) {
		m_newRecordFontRender.Draw(rc);
	}
}