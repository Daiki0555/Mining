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
	/// �摜���X�V
	/// </summary>
	void SpriteUpdate();

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

private:
	enum enFadeState {
		m_enFadeState_FadeIn,								// �t�F�[�h�C��
		m_enFadeState_FadeOut,								// �t�F�[�h�A�E�g
		m_enFadeState_Idle,									// �ҋ@��
	};
	enFadeState		m_fadeState = m_enFadeState_Idle;		// �X�e�[�g

	SpriteRender	m_spriteRender;							// �X�v���C�g�����_�[

	float			m_alpha = 2.0f;							// �����x
};

