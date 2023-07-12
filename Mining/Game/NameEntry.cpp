#include "stdafx.h"
#include "NameEntry.h"

#include "SaveDataManager.h"

namespace
{
	const Vector3	SPELL_FONT_POS = Vector3(-600.0f, 0.0f, 0.0f);	//�p�����̍��W�B
	const Vector3	INPUT_NAME_POS = Vector3(0.0f, 200.0f, 0.0f);	//���͕����̍��W�B
	const int		BUFFER_SIZE = 256;								//�o�b�t�@�[�T�C�Y�B
	const int		SPELL_NUM_FIRST = 65;							//char�^��A�B
	const int		SPELL_NUM_MAX = 26;								//�X�y���̍ő吔�B
	const int		SPELL_ROW_MAX = 13;								//������̍s���̍ő�B
	const int		SPELL_COLUMN_MAX = 2;							//������̗񐔂̍ő�B
	const int		INPUT_NAME_MAX = 5;								//���O�̍ő吔�B
	const int		INPUT_NAME_MIN = 0;								//���O�̍ŏ����B
	const float		SPELL_DURATION = 100.0f;						//�����̊Ԋu�B
	const float		SPELL_FONT_SCALE = 2.0f;						//�p�����̊g�嗦�B
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
	m_backGroundSpriteRender.Init("Assets/Sprite/UI/Scene/nameEntry.DDS", 1920.0f, 1080.0f);

	//���͕����̐ݒ�B
	m_inputNameFontRender.SetText(L"");
	m_inputNameFontRender.SetPosition(INPUT_NAME_POS);
	m_inputNameFontRender.SetColor(Vector4::Black);

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
	}

	m_debugFontRender.SetColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));

	return true;
}

void NameEntry::Update()
{
	Input();

	CursorAnimation();

	wchar_t text[BUFFER_SIZE];
	swprintf_s(text, BUFFER_SIZE, L"%.2f", m_cursorTimer);
	m_debugFontRender.SetText(text);

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
	else if (g_pad[0]->IsTrigger(enButtonA)) {

		InputName();
	}
	else if (g_pad[0]->IsTrigger(enButtonB)) {

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
	if (m_inputNameNum >= INPUT_NAME_MAX) {
		return;
	}

	//���͂��镶�����擾�B
	char name[3];
	wchar_t* getText = (wchar_t*)m_spellFontRender[m_cursor].GetText();

	//wchar_t��char�ɕϊ��B
	wcstombs(name, getText, sizeof(getText));

	m_inputName[m_inputNameNum] = name[1];
	m_inputName[m_inputNameNum + 1] = '\0';

	//���͐������Z�B
	m_inputNameNum++;

	NameUpdate();
}

void NameEntry::EraseName()
{
	if (m_inputNameNum <= INPUT_NAME_MIN) {
		return;
	}

	//�����̕������폜�B
	m_inputName[m_inputNameNum - 1] = '\0';

	//���͐������Z�B
	m_inputNameNum--;

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

void NameEntry::Render(RenderContext& rc)
{
	//�w�i�̕`��B
	m_backGroundSpriteRender.Draw(rc);

	//������̕`��B
	for (int i = 0; i < SPELL_NUM_MAX; i++) {
		m_spellFontRender[i].Draw(rc);
	}

	//���͖��O�̕`��B
	m_inputNameFontRender.Draw(rc);

	m_debugFontRender.Draw(rc);
}