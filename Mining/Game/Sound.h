#pragma once
#include "sound/SoundSource.h"

class Sound : public IGameObject
{
public:
	Sound();
	~Sound();

	bool Start();

	enum enSoundState {
		m_enSoundState_TitleBGM,				// タイトル
		m_enSoundState_GameBGM,					// ゲーム
		m_enSoundState_ResultBGM,				// リザルト
		m_enSoundState_FixedSE,					// 決定(B)
		m_enSoundState_CancelSE,				// キャンセル(A)
		m_enSoundState_NameEntryEndSE,			// ネームエントリー終了
		m_enSoundState_DigSE,					// 採掘
		m_enSoundState_GetSE,					// クリスタル獲得
		m_enSoundState_DamageSE,				// ダメージ
	};

	/// <summary>
	/// 鳴らすBGMを指定する
	/// </summary>
	void SetSoundBGM(enSoundState state);

	/// <summary>
	/// BGMを削除する
	/// </summary>
	void DeleteBGM();

	/// <summary>
	/// 鳴らすSEを指定する
	/// </summary>
	/// <param name="state"></param>
	void SetSoundSE(enSoundState state);

public:
	/// <summary>
	/// BGMの停止を行うかどうか決定する
	/// </summary>
	/// <param name="flag">trueなら停止しない</param>
	void SetStoPflag (bool flag) {
		m_isStop = flag;
	}

private:
	enSoundState	m_soundState;				// BGMのステート
	SoundSource*	m_bgm = nullptr;			// サウンドソース
	bool			m_isDelete = false;			// BGMを削除中かどうか
	bool			m_isStop = false;			// BGMを停止するかどうか
	float			m_timer = 0.0f;				// タイマー
};

