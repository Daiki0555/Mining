#pragma once

class NameEntry : public IGameObject
{
public:
	NameEntry();
	~NameEntry();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	/// <summary>
	/// ���͏����B
	/// </summary>
	void Input();

	/// <summary>
	/// �J�[�\���̍X�V�����B
	/// </summary>
	void CursorUpdate();

	/// <summary>
	/// ���O�̓��͏����B
	/// </summary>
	void InputName();

	/// <summary>
	/// ���O�̍폜�����B
	/// </summary>
	void EraseName();

	/// <summary>
	/// ���O�̍X�V�����B
	/// </summary>
	void NameUpdate();

	/// <summary>
	/// �I�������B
	/// </summary>
	void End();

	/// <summary>
	/// �J�[�\���̃A�j���[�V���������B
	/// </summary>
	void CursorAnimation();

private:
	SpriteRender	m_backGroundSpriteRender;		//�w�i�摜�B
	FontRender		m_spellFontRender[26];			//�p�����B
	FontRender		m_inputNameFontRender;			//���͕����B
	char			m_inputName[256];				//���͂��ꂽ���O�B
	int				m_score = 13;					//�X�R�A�B
	int				m_cursor = 0;					//���ɕ��ׂ����̃J�[�\���B
	int				m_cursorVertical = 0;			//�c�J�[�\���B
	int				m_cursorHorizontal = 0;			//���J�[�\���B
	int				m_cursorOld = 0;				//�O��̓��́B
	int				m_inputNameNum = 0;				//�����̓��͐��B
	float			m_cursorTimer = 0.0f;			//�J�[�\���p�^�C�}�[�B

	FontRender m_debugFontRender;
};

