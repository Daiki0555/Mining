#pragma once

class NameEntry : public IGameObject
{
public:
	NameEntry();
	~NameEntry();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

public:
	/// <summary>
	/// �X�R�A��ݒ�B
	/// </summary>
	/// <param name="score"></param>
	void SetScore(const int score)
	{
		m_score = score;
	}

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

	/// <summary>
	/// ���͕����̃A�j���[�V���������B
	/// </summary>
	void NameAnimation();

private:
	//�����̃A�j���[�V�����X�e�[�g�B
	enum AnimationState
	{
		enState_Input,		//�ǉ��B
		enState_Erase,		//�폜�B
		enState_Idle,		//�ҋ@�B
	};

private:
	SpriteRender	m_backGroundSpriteRender;			//�w�i�摜�B
	FontRender		m_spellFontRender[26];				//�p�����B
	FontRender		m_inputNameFontRender;				//���͕����B
	FontRender		m_animFontRender;					//�A�j���[�V�����p�����B
	Vector3			m_bezierPos[3];						//�x�W�F�Ȑ��̍��W�B
	AnimationState	m_animationState = enState_Idle;	//�A�j���[�V�����X�e�[�g�B	
	char			m_inputName[256];					//���͂��ꂽ���O�B
	int				m_score = 0;						//�X�R�A�B
	int				m_cursor = 0;						//���ɕ��ׂ����̃J�[�\���B
	int				m_cursorVertical = 0;				//�c�J�[�\���B
	int				m_cursorHorizontal = 0;				//���J�[�\���B
	int				m_cursorOld = 0;					//�O��̓��́B
	int				m_inputNameNum = 0;					//�����̓��͐��B
	float			m_cursorTimer = 0.0f;				//�J�[�\���p�^�C�}�[�B
	float			m_animTimer = 0.0f;					//�A�j���[�V�����p�^�C�}�[�B
};

