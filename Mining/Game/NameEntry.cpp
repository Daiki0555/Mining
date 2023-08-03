#include "stdafx.h"
#include "NameEntry.h"

#include "SaveDataManager.h"
#include "Ranking.h"
#include "UI/Fade.h"
#include "Sound.h"

namespace
{
	const Vector3	SPELL_FONT_POS = Vector3(-600.0f, 0.0f, 0.0f);	//�p�����̍��W�B
	const Vector3	INPUT_NAME_POS = Vector3(-60.0f, 180.0f, 0.0f);	//���͕����̍��W�B
	const Vector3	FONT_POSITION = Vector3(-250.0f, -450.0f, 0.0f);//������������̍��W�B
	const int		SPELL_NUM_FIRST = 65;							//char�^��A�B
	const int		SPELL_NUM_MAX = 26;								//�X�y���̍ő吔�B
	const int		SPELL_ROW_MAX = 13;								//������̍s���̍ő�B
	const int		SPELL_COLUMN_MAX = 2;							//������̗񐔂̍ő�B
	const int		INPUT_NAME_MAX = 5;								//���O�̍ő吔�B
	const int		INPUT_NAME_MIN = 0;								//���O�̍ŏ����B
	const int		BEZIER_RANGE = 200;								//�x�W�F�̒��_�͈̔́B
	const float		SPELL_DURATION = 100.0f;						//�X�y�������̊Ԋu�B
	const float		INPUT_NAME_DURATION = 21.0f;					//���͕����̊Ԋu�B
	const float		SPELL_FONT_SCALE = 2.0f;						//�p�����̊g�嗦�B
	const float		FONT_SHADOW_OFFSET = 2.0f;						// �s�N�Z���̃I�t�Z�b�g��
	const Vector4	FONT_SHADOW_COLOR = { 1.0f,1.0f,1.0f,1.0f };	// �J���[
}

NameEntry::NameEntry()
{
}

NameEntry::~NameEntry()
{

}

bool NameEntry::Start()
{
	//�w�i�摜�̐ݒ�B
	//m_backGroundSpriteRender.Init("Assets/Sprite/UI/Scene/nameEntry.DDS", 1920.0f, 1080.0f);

	m_level2DRender = new Level2DRender;

	m_level2DRender->Init("Assets/level/level2D/nameEntry.casl", [&](Level2DObjeData& objData) {
		if (objData.EqualObjectName("title") == true) {
			m_backGroundSpriteRender.Init(objData.ddsFilePath, objData.width, objData.height);
			m_backGroundSpriteRender.SetPosition(objData.position);
			m_backGroundSpriteRender.SetRotation(objData.rotation);
			m_backGroundSpriteRender.Update();
			return true;
		}
		if (objData.EqualObjectName("nameEntry") == true) {
			m_nameEnrtySpriteRender.Init(objData.ddsFilePath, objData.width, objData.height);
			m_nameEnrtySpriteRender.SetPosition(objData.position);
			m_nameEnrtySpriteRender.SetRotation(objData.rotation);
			m_nameEnrtySpriteRender.Update();
			return true;
		}
		if (objData.EqualObjectName("userName") == true) {
			m_userNameSpriteRender.Init(objData.ddsFilePath, objData.width, objData.height);
			m_userNameSpriteRender.SetPosition(objData.position);
			m_userNameSpriteRender.SetRotation(objData.rotation);
			m_userNameSpriteRender.Update();
			return true;
		}

		return false;
		});

	//���͕����̐ݒ�B
	m_inputNameFontRender.SetText(L"");
	m_inputNameFontRender.SetPosition(INPUT_NAME_POS);
	m_inputNameFontRender.SetColor(Vector4::Black);
	m_inputNameFontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

	//�A�j���[�V�����p�����̐ݒ�B
	m_animFontRender.SetText(L"");
	m_animFontRender.SetScale(SPELL_FONT_SCALE);
	m_animFontRender.SetColor(Vector4::Black);
	m_animFontRender.SetPivot(Vector2(0.0f, 0.0f));
	m_animFontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

	//��������p�̕����̐ݒ�B
	m_fontRender.SetText(L"START�{�^���œ��͏I��");
	m_fontRender.SetPosition(FONT_POSITION);
	m_fontRender.SetColor(Vector4::Black);
	m_fontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

	//���͂ł��镶���̐ݒ�B
	wchar_t spell;
	wchar_t text[BUFFER_SIZE];
	Vector3 spellPos;

	for (int i = 0; i < SPELL_NUM_MAX; i++) {

		//������ݒ�B
		spell = (SPELL_NUM_FIRST + i);
		//������ɕϊ��B
		swprintf_s(text, BUFFER_SIZE, L"%2c", spell);

		spellPos = Vector3(SPELL_DURATION * i, 0.0f, 0.0f);

		if (i >= SPELL_ROW_MAX) {

			spellPos.x = SPELL_DURATION * (i - SPELL_ROW_MAX);
			spellPos.y = -100.0f;
		}

		//������̐ݒ�B
		m_spellFontRender[i].SetText(text);
		m_spellFontRender[i].SetPosition(SPELL_FONT_POS + spellPos);
		m_spellFontRender[i].SetScale(SPELL_FONT_SCALE);
		m_spellFontRender[i].SetColor(Vector4::Black);
		m_spellFontRender[i].SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);
	}

	//�t�F�[�h�C���B
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();

	m_sound = FindGO<Sound>("sound");

	return true;
}

void NameEntry::Update()
{
	//�t�F�[�h�A�E�g���Ȃ�B
	if (m_isWaitFadeOut) {
		//�t�F�[�h���I�����Ă���Ȃ�B
		if (!m_fade->IsFade()) {
			//�����L���O�V�[���֑J�ځB
			NewGO<Ranking>(0, "ranking");
			DeleteGO(this);
		}
	}
	else {

		Input();
	}

	CursorAnimation();

	NameAnimation();
}

void NameEntry::Input()
{
	//���{�^���������ꂽ��B
	if (g_pad[0]->IsTrigger(enButtonDown)) {

		m_cursorVertical++;

		CursorUpdate();
	}
	//��{�^���������ꂽ��B
	else if (g_pad[0]->IsTrigger(enButtonUp)) {

		m_cursorVertical--;

		CursorUpdate();
	}
	//�E�{�^���������ꂽ��B
	else if (g_pad[0]->IsTrigger(enButtonRight)) {

		m_cursorHorizontal++;

		CursorUpdate();
	}
	//���{�^���������ꂽ��B
	else if (g_pad[0]->IsTrigger(enButtonLeft)) {

		m_cursorHorizontal--;

		CursorUpdate();
	}
	else if (g_pad[0]->IsTrigger(enButtonB)) {

		InputName();
	}
	else if (g_pad[0]->IsTrigger(enButtonA)) {

		EraseName();
	}
	else if (g_pad[0]->IsTrigger(enButtonStart)) {

		End();
	}
}

void NameEntry::CursorUpdate()
{
	//0�`�s��̍ő吔�͈̔͂Ɏ��߂�B
	//0�X�^�[�g�Ȃ̂ōs�񐔂̍ő吔����1�������B
	m_cursorHorizontal = min( max(m_cursorHorizontal, 0), SPELL_ROW_MAX - 1);
	m_cursorVertical = min(max(m_cursorVertical, 0), SPELL_COLUMN_MAX - 1 );

	//���݂̃J�[�\���ʒu�B
	m_cursor = (m_cursorHorizontal % SPELL_ROW_MAX) + (m_cursorVertical * SPELL_ROW_MAX);

	//�J�[�\���^�C�}�[�̏������B
	m_cursorTimer = 0.0f;

	//�ߋ��̃J�[�\���ʒu�̕����F��߂��B
	m_spellFontRender[m_cursorOld].SetColor(Vector4::Black);

	//�ߋ��̃J�[�\���ʒu��ۑ��B
	m_cursorOld = m_cursor;
}

void NameEntry::InputName()
{
	//�������ő吔�Ȃ�ǉ����Ȃ��B�B
	if (m_inputNameNum >= INPUT_NAME_MAX) {
		return;
	}

	//�A�j���[�V�������Ȃ�B
	if (m_animationState != enState_Idle) {
		return;
	}

	//���͂��镶�����擾�B
	char name[3];
	wchar_t* getText = (wchar_t*)m_spellFontRender[m_cursor].GetText();

	//wchar_t��char�ɕϊ��B
	wcstombs(name, getText, sizeof(getText));

	//���C�h�����̂P�ڂ��Ȃ����󔒂Ȃ̂ŁA�z��̂Q�ڂ��當�������B
	m_inputName[m_inputNameNum] = name[1];
	m_inputName[m_inputNameNum + 1] = '\0';

	//���͐������Z�B
	m_inputNameNum++;

	//�A�j���[�V�����p������ݒ�B
	m_animFontRender.SetText(getText);
	m_animationState = enState_Input;
	Vector3 inputPos = m_spellFontRender[m_cursor].GetPosition();

	m_bezierPos[0] = inputPos;
	m_bezierPos[1] = Vector3(inputPos.x + rand() % BEZIER_RANGE, 0.0f, 0.0f);
	m_bezierPos[2] = INPUT_NAME_POS + Vector3((m_inputNameNum * INPUT_NAME_DURATION), 0.0f, 0.0f);
}

void NameEntry::EraseName()
{
	//�������ŏ����Ȃ�����Ȃ��B
	if (m_inputNameNum <= INPUT_NAME_MIN) {
		return;
	}

	//�A�j���[�V�������Ȃ�B
	if (m_animationState != enState_Idle) {
		return;
	}

	//�A�j���[�V�����p������ݒ�B
	wchar_t text[2];
	text[1] = L'\0';
	char spell[2];
	spell[0] = m_inputName[m_inputNameNum - 1];
	spell[1] = '\0';
	mbstowcs(text, spell, sizeof(spell));

	//�����̕������폜�B
	m_inputName[m_inputNameNum - 1] = '\0';

	//���͐������Z�B
	m_inputNameNum--;

	m_animFontRender.SetText(text);
	m_animationState = enState_Erase;
	m_animFontRender.SetPosition(INPUT_NAME_POS + Vector3((m_inputNameNum * INPUT_NAME_DURATION), 0.0f, 0.0f));
	m_animFontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

	NameUpdate();
}

void NameEntry::NameUpdate()
{
	//���͖��O��ݒ�B
	wchar_t text[BUFFER_SIZE];
	swprintf_s(text, BUFFER_SIZE, L"%hs", m_inputName);
	m_inputNameFontRender.SetText(text);
}

void NameEntry::End()
{
	//���������͂���ĂȂ��Ȃ�B
	if (m_inputNameNum <= INPUT_NAME_MIN) {
		return;
	}

	SaveDataManager SaveDataMng;
	SaveDataManager::SaveData data;

	//�f�[�^���������B
	SaveDataMng.Init(data);
	//�f�[�^�̃��[�h�B
	SaveDataMng.Load(data);

	//�Z�[�u�f�[�^�ɃX�R�A�����ă\�[�g����B
	int num = SaveDataMng.Sort(data, m_score);
	//���O��ۑ��B
	SaveDataMng.SetPlayerName(m_inputName, num);

	//�Z�[�u�B
	SaveDataMng.Save(data);

	//�t�F�[�h�A�E�g�J�n�B
	m_fade->FadeOut();
	m_isWaitFadeOut = true;
	m_sound->DeleteBGM();
}

void NameEntry::CursorAnimation()
{
	m_cursorTimer += g_gameTime->GetFrameDeltaTime();

	if (m_cursorTimer > 1.0f) {
		m_cursorTimer = 0.0f;
	}

	//���݂̃J�[�\���ʒu�̐F��ύX�B
	m_spellFontRender[m_cursor].SetColor(Vector4(1.0f, m_cursorTimer, m_cursorTimer, 1.0f));
}

void NameEntry::NameAnimation()
{
	if (m_animationState == enState_Idle) {
		return;
	}

	m_animTimer += g_gameTime->GetFrameDeltaTime() * 2.0f;

	//���Ԃ��o�߂�����B
	if (m_animTimer > 1.0f) {

		m_animFontRender.SetColor(Vector4::Black);

		NameUpdate();

		m_animationState = enState_Idle;
		m_animTimer = 0.0f;
	}

	Vector3 bezier[3];
	float alpha = 1.0f - m_animTimer;

	switch (m_animationState)
	{
	case enState_Input:
		//�x�W�F�Ȑ��𗘗p���č��W��ݒ�B
		bezier[0].Lerp(m_animTimer, m_bezierPos[0], m_bezierPos[1]);
		bezier[1].Lerp(m_animTimer, m_bezierPos[1], m_bezierPos[2]);
		bezier[2].Lerp(m_animTimer, bezier[0], bezier[1]);

		m_animFontRender.SetPosition(bezier[2]);
		m_animFontRender.SetScale(SPELL_FONT_SCALE - m_animTimer);
		break;

	case enState_Erase:
		m_animFontRender.SetColor(Vector4(0.0f, 0.0f, 0.0f, alpha));
		break;
	}
}

void NameEntry::Render(RenderContext& rc)
{
	//�w�i�̕`��B
	m_backGroundSpriteRender.Draw(rc);
	m_nameEnrtySpriteRender.Draw(rc);
	m_userNameSpriteRender.Draw(rc);
	m_fontRender.Draw(rc);

	//������̕`��B
	for (int i = 0; i < SPELL_NUM_MAX; i++) {
		m_spellFontRender[i].Draw(rc);
	}

	//���͖��O�̕`��B
	m_inputNameFontRender.Draw(rc);

	//�A�j���[�V���������̕`��B
	if (m_animationState != enState_Idle) {
		m_animFontRender.Draw(rc);
	}
}