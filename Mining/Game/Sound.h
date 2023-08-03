#pragma once
#include "sound/SoundSource.h"

class Sound : public IGameObject
{
public:
	Sound();
	~Sound();

	bool Start();

	enum enSoundState {
		m_enSoundState_TitleBGM,				// �^�C�g��
		m_enSoundState_GameBGM,					// �Q�[��
		m_enSoundState_ResultBGM,				// ���U���g
		m_enSoundState_FixedSE,					// ����
		m_enSoundState_CancelSE,				// �L�����Z��
		m_enSoundState_NewScoreSE,				// �V�L�^
		m_enSoundState_NameEntryEndSE,			// �l�[���G���g���[�I��
		m_enSoundState_DigSE,					// �̌@
		m_enSoundState_GetSE,					// �N���X�^���l��
		m_enSoundState_DamageSE,				// �_���[�W
	};

	/// <summary>
	/// �炷���y���w�肷��
	/// </summary>
	void SetSoundBGM(enSoundState state);

	/// <summary>
	/// BGM���폜����
	/// </summary>
	void DeleteBGM();

public:

	/// <summary>
	/// BGM�̒�~���s�����ǂ������肷��
	/// </summary>
	/// <param name="flag">true�Ȃ��~���Ȃ�</param>
	void SetStoPflag (bool flag) {
		m_isStop = flag;
	}

private:
	enSoundState	m_soundState;				// BGM�̃X�e�[�g
	SoundSource*	m_bgm = nullptr;			// �T�E���h�\�[�X
	bool			m_isDelete = false;			// BGM���폜�����ǂ���
	bool			m_isStop = false;			// BGM���~���邩�ǂ���
	float			m_timer = 0.0f;				// �^�C�}�[
};

