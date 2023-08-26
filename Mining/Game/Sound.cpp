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
	g_soundEngine->ResistWaveFileBank(m_enSoundState_FixedSE, "Assets/sound/fixed.wav");
	g_soundEngine->ResistWaveFileBank(m_enSoundState_CancelSE, "Assets/sound/cancel.wav");
	g_soundEngine->ResistWaveFileBank(m_enSoundState_NameEntryEndSE, "Assets/sound/entryEnd.wav");
	g_soundEngine->ResistWaveFileBank(m_enSoundState_DigSE, "Assets/sound/dig.wav");
	g_soundEngine->ResistWaveFileBank(m_enSoundState_GetSE, "Assets/sound/getCrystal.wav");
	g_soundEngine->ResistWaveFileBank(m_enSoundState_DamageSE, "Assets/sound/damage.wav");

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

void Sound::SetSoundSE(enSoundState state) 
{
	SoundSource* m_se = NewGO<SoundSource>(0);
	m_se->Init(state);
	m_se->SetVolume(VOLUME);
	m_se->Play(false);
}