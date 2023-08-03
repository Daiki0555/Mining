#include "stdafx.h"
#include "NameEntry.h"

#include "SaveDataManager.h"
#include "Ranking.h"
#include "UI/Fade.h"
#include "Sound.h"

namespace
{
	const Vector3	SPELL_FONT_POS = Vector3(-600.0f, 0.0f, 0.0f);	//英文字の座標。
	const Vector3	INPUT_NAME_POS = Vector3(-60.0f, 180.0f, 0.0f);	//入力文字の座標。
	const Vector3	FONT_POSITION = Vector3(-250.0f, -450.0f, 0.0f);//操作説明文字の座標。
	const int		SPELL_NUM_FIRST = 65;							//char型のA。
	const int		SPELL_NUM_MAX = 26;								//スペルの最大数。
	const int		SPELL_ROW_MAX = 13;								//文字列の行数の最大。
	const int		SPELL_COLUMN_MAX = 2;							//文字列の列数の最大。
	const int		INPUT_NAME_MAX = 5;								//名前の最大数。
	const int		INPUT_NAME_MIN = 0;								//名前の最小数。
	const int		BEZIER_RANGE = 200;								//ベジェの中点の範囲。
	const float		SPELL_DURATION = 100.0f;						//スペル文字の間隔。
	const float		INPUT_NAME_DURATION = 21.0f;					//入力文字の間隔。
	const float		SPELL_FONT_SCALE = 2.0f;						//英文字の拡大率。
	const float		FONT_SHADOW_OFFSET = 2.0f;						// ピクセルのオフセット量
	const Vector4	FONT_SHADOW_COLOR = { 1.0f,1.0f,1.0f,1.0f };	// カラー
}

NameEntry::NameEntry()
{
}

NameEntry::~NameEntry()
{

}

bool NameEntry::Start()
{
	//背景画像の設定。
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

	//入力文字の設定。
	m_inputNameFontRender.SetText(L"");
	m_inputNameFontRender.SetPosition(INPUT_NAME_POS);
	m_inputNameFontRender.SetColor(Vector4::Black);
	m_inputNameFontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

	//アニメーション用文字の設定。
	m_animFontRender.SetText(L"");
	m_animFontRender.SetScale(SPELL_FONT_SCALE);
	m_animFontRender.SetColor(Vector4::Black);
	m_animFontRender.SetPivot(Vector2(0.0f, 0.0f));
	m_animFontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

	//操作説明用の文字の設定。
	m_fontRender.SetText(L"STARTボタンで入力終了");
	m_fontRender.SetPosition(FONT_POSITION);
	m_fontRender.SetColor(Vector4::Black);
	m_fontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

	//入力できる文字の設定。
	wchar_t spell;
	wchar_t text[BUFFER_SIZE];
	Vector3 spellPos;

	for (int i = 0; i < SPELL_NUM_MAX; i++) {

		//文字を設定。
		spell = (SPELL_NUM_FIRST + i);
		//文字列に変換。
		swprintf_s(text, BUFFER_SIZE, L"%2c", spell);

		spellPos = Vector3(SPELL_DURATION * i, 0.0f, 0.0f);

		if (i >= SPELL_ROW_MAX) {

			spellPos.x = SPELL_DURATION * (i - SPELL_ROW_MAX);
			spellPos.y = -100.0f;
		}

		//文字列の設定。
		m_spellFontRender[i].SetText(text);
		m_spellFontRender[i].SetPosition(SPELL_FONT_POS + spellPos);
		m_spellFontRender[i].SetScale(SPELL_FONT_SCALE);
		m_spellFontRender[i].SetColor(Vector4::Black);
		m_spellFontRender[i].SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);
	}

	//フェードイン。
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();

	m_sound = FindGO<Sound>("sound");

	return true;
}

void NameEntry::Update()
{
	//フェードアウト中なら。
	if (m_isWaitFadeOut) {
		//フェードが終了しているなら。
		if (!m_fade->IsFade()) {
			//ランキングシーンへ遷移。
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
	//下ボタンが押されたら。
	if (g_pad[0]->IsTrigger(enButtonDown)) {

		m_cursorVertical++;

		CursorUpdate();
	}
	//上ボタンが押されたら。
	else if (g_pad[0]->IsTrigger(enButtonUp)) {

		m_cursorVertical--;

		CursorUpdate();
	}
	//右ボタンが押されたら。
	else if (g_pad[0]->IsTrigger(enButtonRight)) {

		m_cursorHorizontal++;

		CursorUpdate();
	}
	//左ボタンが押されたら。
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
	//0～行列の最大数の範囲に収める。
	//0スタートなので行列数の最大数から1を引く。
	m_cursorHorizontal = min( max(m_cursorHorizontal, 0), SPELL_ROW_MAX - 1);
	m_cursorVertical = min(max(m_cursorVertical, 0), SPELL_COLUMN_MAX - 1 );

	//現在のカーソル位置。
	m_cursor = (m_cursorHorizontal % SPELL_ROW_MAX) + (m_cursorVertical * SPELL_ROW_MAX);

	//カーソルタイマーの初期化。
	m_cursorTimer = 0.0f;

	//過去のカーソル位置の文字色を戻す。
	m_spellFontRender[m_cursorOld].SetColor(Vector4::Black);

	//過去のカーソル位置を保存。
	m_cursorOld = m_cursor;
}

void NameEntry::InputName()
{
	//文字が最大数なら追加しない。。
	if (m_inputNameNum >= INPUT_NAME_MAX) {
		return;
	}

	//アニメーション中なら。
	if (m_animationState != enState_Idle) {
		return;
	}

	//入力する文字を取得。
	char name[3];
	wchar_t* getText = (wchar_t*)m_spellFontRender[m_cursor].GetText();

	//wchar_tをcharに変換。
	wcstombs(name, getText, sizeof(getText));

	//ワイド文字の１つ目がなぜか空白なので、配列の２つ目から文字を取る。
	m_inputName[m_inputNameNum] = name[1];
	m_inputName[m_inputNameNum + 1] = '\0';

	//入力数を加算。
	m_inputNameNum++;

	//アニメーション用文字を設定。
	m_animFontRender.SetText(getText);
	m_animationState = enState_Input;
	Vector3 inputPos = m_spellFontRender[m_cursor].GetPosition();

	m_bezierPos[0] = inputPos;
	m_bezierPos[1] = Vector3(inputPos.x + rand() % BEZIER_RANGE, 0.0f, 0.0f);
	m_bezierPos[2] = INPUT_NAME_POS + Vector3((m_inputNameNum * INPUT_NAME_DURATION), 0.0f, 0.0f);
}

void NameEntry::EraseName()
{
	//文字が最小数なら消さない。
	if (m_inputNameNum <= INPUT_NAME_MIN) {
		return;
	}

	//アニメーション中なら。
	if (m_animationState != enState_Idle) {
		return;
	}

	//アニメーション用文字を設定。
	wchar_t text[2];
	text[1] = L'\0';
	char spell[2];
	spell[0] = m_inputName[m_inputNameNum - 1];
	spell[1] = '\0';
	mbstowcs(text, spell, sizeof(spell));

	//末尾の文字を削除。
	m_inputName[m_inputNameNum - 1] = '\0';

	//入力数を減算。
	m_inputNameNum--;

	m_animFontRender.SetText(text);
	m_animationState = enState_Erase;
	m_animFontRender.SetPosition(INPUT_NAME_POS + Vector3((m_inputNameNum * INPUT_NAME_DURATION), 0.0f, 0.0f));
	m_animFontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

	NameUpdate();
}

void NameEntry::NameUpdate()
{
	//入力名前を設定。
	wchar_t text[BUFFER_SIZE];
	swprintf_s(text, BUFFER_SIZE, L"%hs", m_inputName);
	m_inputNameFontRender.SetText(text);
}

void NameEntry::End()
{
	//文字が入力されてないなら。
	if (m_inputNameNum <= INPUT_NAME_MIN) {
		return;
	}

	SaveDataManager SaveDataMng;
	SaveDataManager::SaveData data;

	//データを初期化。
	SaveDataMng.Init(data);
	//データのロード。
	SaveDataMng.Load(data);

	//セーブデータにスコアを入れてソートする。
	int num = SaveDataMng.Sort(data, m_score);
	//名前を保存。
	SaveDataMng.SetPlayerName(m_inputName, num);

	//セーブ。
	SaveDataMng.Save(data);

	//フェードアウト開始。
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

	//現在のカーソル位置の色を変更。
	m_spellFontRender[m_cursor].SetColor(Vector4(1.0f, m_cursorTimer, m_cursorTimer, 1.0f));
}

void NameEntry::NameAnimation()
{
	if (m_animationState == enState_Idle) {
		return;
	}

	m_animTimer += g_gameTime->GetFrameDeltaTime() * 2.0f;

	//時間が経過したら。
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
		//ベジェ曲線を利用して座標を設定。
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
	//背景の描画。
	m_backGroundSpriteRender.Draw(rc);
	m_nameEnrtySpriteRender.Draw(rc);
	m_userNameSpriteRender.Draw(rc);
	m_fontRender.Draw(rc);

	//文字列の描画。
	for (int i = 0; i < SPELL_NUM_MAX; i++) {
		m_spellFontRender[i].Draw(rc);
	}

	//入力名前の描画。
	m_inputNameFontRender.Draw(rc);

	//アニメーション文字の描画。
	if (m_animationState != enState_Idle) {
		m_animFontRender.Draw(rc);
	}
}