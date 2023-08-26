#pragma once
class Fade :public IGameObject
{
public:
	Fade();
	~Fade();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// �t�F�[�h�C���̏���
	/// </summary>
	void FadeIn() {
		m_fadeState = m_enFadeState_FadeIn;
	}

	/// <summary>
	/// �t�F�[�h�A�E�g�̏���
	/// </summary>
	void FadeOut() {
		m_fadeState = m_enFadeState_FadeOut;
	}

	/// <summary>
	/// �t�F�[�h�����ǂ����B
	/// </summary>
	/// <returns></returns>
	const bool IsFade() const
	{
		return m_fadeState != m_enFadeState_Idle;
	}

	/// <summary>
	/// Loading�̕�����\�����邩���肷��
	/// </summary>
	/// <param name="flag">true�Ȃ�`�悷��</param>
	void SetDrawFlag(bool flag) 
	{
		m_isDraw = flag;
	}

private:
	/// <summary>
	/// �摜���X�V
	/// </summary>
	void SpriteUpdate();

	/// <summary>
	/// �摜����]������
	/// </summary>
	void RotationImage();

private:
	enum enFadeState {
		m_enFadeState_FadeIn,								// �t�F�[�h�C��
		m_enFadeState_FadeOut,								// �t�F�[�h�A�E�g
		m_enFadeState_Idle,									// �ҋ@��
	};
	enFadeState		m_fadeState = m_enFadeState_Idle;		// �X�e�[�g

	SpriteRender	m_spriteRender;							// �X�v���C�g�����_�[
	SpriteRender	m_imageSpriteRender;					// �X�v���C�g�����_�[
	FontRender		m_fontRender;							// �t�H���g�����_�[

	bool			m_isDraw = true;						// �`�悷�邩�ǂ���
	float			m_alpha = 1.0f;							// �����x
	float			m_timer = 0.0f;							// �^�C�}�[
};

