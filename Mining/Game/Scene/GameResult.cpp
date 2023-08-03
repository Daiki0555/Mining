#include "stdafx.h"
#include "GameResult.h"

#include "SaveDataManager.h"
#include "NameEntry.h"
#include "Title.h"
#include "UI/Fade.h"
#include "Sound.h"

namespace
{
	const Vector3	CRYSTAL_FONT_POS = Vector3(-50.0f, 320.0f, 0.0f);					//クリスタル個数文字の座標。
	const Vector3	NEWRECORD_FONT_POS = Vector3(-175.0f, -250.0f, 0.0f);				//新記録文字の座標。
	const int		CRYSTAL_POINTS[CRYSTAL_CATEGORY_MAX] = { 10, 100, 1000, 10000 };	//クリスタルのポイント。
	const float		CRYSTAL_FONT_SCALE = 1.3f;											//クリスタル個数文字の拡大率。
	const float		NEWRECORD_TIMER_MAX = 1.0f;											//新記録用タイマーの最大値。
	const float		NEWRECORD_TIMER_MIN = 0.0f;											//新記録用タイマーの最小値。
	const float		FONT_SCALE = 0.5f;													// フォントのスケール 
	const float		FONT_SHADOW_OFFSET = 2.0f;											// ピクセルのオフセット量
	const Vector4	FONT_SHADOW_COLOR = Vector4(1.0f, 1.0f, 1.0f, 1.0f);				// カラー
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

	////背景画像の設定。
	//m_backGroundSpriteRender.Init("Assets/Sprite/UI/Scene/result.DDS", 1920.0f, 1080.0f);

	m_level2DRender = new Level2DRender;

	m_level2DRender->Init("Assets/level/level2D/result.casl", [&](Level2DObjeData& objData) {
		if (objData.EqualObjectName("title") == true) {
			m_backGroundSpriteRender.Init(objData.ddsFilePath, objData.width, objData.height);
			m_backGroundSpriteRender.SetPosition(objData.position);
			m_backGroundSpriteRender.SetRotation(objData.rotation);
			m_backGroundSpriteRender.Update();
			return true;
		}
		if (objData.EqualObjectName("result") == true) {
			m_resultSpriteRender.Init(objData.ddsFilePath, objData.width, objData.height);
			m_resultSpriteRender.SetPosition(objData.position);
			m_resultSpriteRender.SetRotation(objData.rotation);
			m_resultSpriteRender.Update();
			return true;
		}
		if (objData.EqualObjectName("scoreBoard") == true) {
			m_scoreBoardSpriteRender.Init(objData.ddsFilePath, objData.width, objData.height);
			m_scoreBoardSpriteRender.SetPosition(objData.position);
			m_scoreBoardSpriteRender.SetRotation(objData.rotation);
			m_scoreBoardSpriteRender.Update();
			return true;
		}

		return false;
		});

	//鉱石個数文字の設定。
	wchar_t text[BUFFER_SIZE];
	swprintf_s(text, BUFFER_SIZE, L"%02d \n\n%02d \n\n%02d \n\n%02d \n\n\n%d",
				m_haveCristals[0], m_haveCristals[1], m_haveCristals[2], m_haveCristals[3], m_newScore);
	m_crystalFontRender.SetText(text);
	m_crystalFontRender.SetPosition(CRYSTAL_FONT_POS);
	m_crystalFontRender.SetScale(CRYSTAL_FONT_SCALE);
	m_crystalFontRender.SetColor(Vector4::Black);
	m_crystalFontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

	//新記録文字の設定。
	m_newRecordFontRender.SetText(L"NEW  RECORD!!!");
	m_newRecordFontRender.SetPosition(NEWRECORD_FONT_POS);
	m_newRecordFontRender.SetColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	m_newRecordFontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);

	//フェードイン。
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();

	m_sound = FindGO<Sound>("sound");
	m_sound->SetSoundBGM(m_sound->m_enSoundState_ResultBGM);

	return true;
}

void GameResult::CalcScore()
{
	//スコアを計算。
	for (int i = 0; i < CRYSTAL_CATEGORY_MAX; i++) {

		m_newScore += CRYSTAL_POINTS[i] * m_haveCristals[i];
	}

	//セーブデータを読み込んでハイスコアかどうか確認。
	SaveDataManager saveDataMng;
	SaveDataManager::SaveData data;
	saveDataMng.Load(data);

	//スコアがランキングのスコアより上なら。
	if (m_newScore > data.score[9]) {
		m_isNewRecord = true;
	}
}

void GameResult::Update()
{
	if (m_isWaitFadeOut) {

		//フェードが終了しているなら。
		if (!m_fade->IsFade()) {
			TransitionScene();
		}
	}
	else {
		//Bボタンが押されたら。
		if (g_pad[0]->IsTrigger(enButtonB)) {
			m_fade->FadeOut();
			m_isWaitFadeOut = true;
		}
	}

	DrawScore();
}

void GameResult::DrawScore()
{
	//新記録時の文字を追加。
	if (m_isNewRecord) {

		m_newRecordTimer += g_gameTime->GetFrameDeltaTime();

		if (m_newRecordTimer > NEWRECORD_TIMER_MAX) {
			m_newRecordTimer = NEWRECORD_TIMER_MIN;
		}

		// (-t^2 + 2t) - 1
		float alpha = fabsf(pow(m_newRecordTimer, 2.0f) + (2.0f * m_newRecordTimer) - 1.0f);
		alpha = min( max( alpha, NEWRECORD_TIMER_MIN), NEWRECORD_TIMER_MAX);

		//透明度を設定。
		m_newRecordFontRender.SetColor(Vector4(alpha, 0.0f, 0.0f, alpha));
		m_newRecordFontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, { alpha ,alpha ,alpha, 1.0f});
	}
}

void GameResult::TransitionScene()
{
	//スコアがランキングのスコアより上なら。
	if (m_isNewRecord) {
		//ネームエントリーへ遷移。
		NameEntry* nameEntry = NewGO<NameEntry>(0, "nameEntry");
		nameEntry->SetScore(m_newScore);
	}
	else {
		//タイトルへ遷移。
		NewGO<Title>(0, "title");
		// BGMを削除する
		m_sound->DeleteBGM();
	}

	DeleteGO(this);
}

void GameResult::Render(RenderContext& rc)
{
	m_backGroundSpriteRender.Draw(rc);
	m_resultSpriteRender.Draw(rc);
	m_scoreBoardSpriteRender.Draw(rc);

	m_crystalFontRender.Draw(rc);

	if (m_isNewRecord) {
		m_newRecordFontRender.Draw(rc);
	}
}