#include "stdafx.h"
#include "Sound.h"

#include "sound/SoundEngine.h"

namespace 
{
	const float VOLUME = 0.5f;
	const float DOWN_VOLUME = 0.4f;
}

Sound::Sound()
{
}

Sound::~Sound()
{
}

bool Sound::Start()
{
	// BGM‚ð“Ç‚Ýž‚Þ
	g_soundEngine->ResistWaveFileBank(m_enSoundState_TitleBGM, "Assets/sound/title.wav");
	g_soundEngine->ResistWaveFileBank(m_enSoundState_GameBGM, "Assets/sound/game.wav");
	g_soundEngine->ResistWaveFileBank(m_enSoundState_ResultBGM, "Assets/sound/result.wav");

	// SE
	//g_soundEngine->ResistWaveFileBank(m_enSoundState_FixedSE, "");
	//g_soundEngine->ResistWaveFileBank(m_enSoundState_CancelSE, "");
	//g_soundEngine->ResistWaveFileBank(m_enSoundState_NewScoreSE, "");
	//g_soundEngine->ResistWaveFileBank(m_enSoundState_NameEntryEndSE, "");
	//g_soundEngine->ResistWaveFileBank(m_enSoundState_DigSE, "");
	//g_soundEngine->ResistWaveFileBank(m_enSoundState_GetSE, "");
	//g_soundEngine->ResistWaveFileBank(m_enSoundState_DamageSE, "");

	return true;
}

void Sound::SetSoundBGM(enSoundState state) 
{
	if (m_isStop) {
		return;
	}

	if (m_bgm != nullptr) {
		m_bgm->Stop();
	}
	else {
		m_bgm = NewGO<SoundSource>(0);
	}

	m_bgm->Init(state);
	m_bgm->SetVolume(VOLUME);
	m_bgm->Play(true);
}

void Sound:: DeleteBGM()
{
	if (!m_isDelete) {
		return;
	}

	m_timer -= (g_gameTime->GetFrameDeltaTime() * DOWN_VOLUME);
	m_bgm->SetVolume(m_timer);

	if (m_timer <= 0.0f) {
		m_isDelete = false;
		m_bgm->Stop();
		m_timer = 0.0f;
	}
}