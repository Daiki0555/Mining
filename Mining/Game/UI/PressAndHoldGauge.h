#pragma once
class Player;
class PressAndHoldGauge:public IGameObject
{
public:
	PressAndHoldGauge();
	~PressAndHoldGauge();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void ChangeGaugeAngle();							// �Q�[�W�̊p�x��ύX
	void ChangeGaugePosition();							// �Q�[�W�̍��W��ύX
	void SetFontRender();								// �t�H���g�����_�[�̕\��

private:
	SpriteRender	m_spriteRenderCircle;				// �X�v���C�g�����_�[
	SpriteRender	m_spriteRenderCircleBase;			// �X�v���C�g�����_�[(�x�[�X)
	
	FontRender		m_fontRender;						// �t�H���g�����_�[

	Player*			m_player = nullptr;					// �v���C���[

	bool			m_changeGaugeValueFlag = false;		// true�Ȃ瑝���Afalse�Ȃ猸��������
	bool			m_maxGaugeValueFlag = false;		// �l���ő傩�ǂ���

	struct GaugeStatus {
		Vector2		m_position = Vector2::Zero;			// ���W
		float		m_angle = 0.0f;						// �Q�[�W�̊p�x
		float		m_maxSize = 0.0f;					// �Q�[�W�̍ő�
		float		m_minSize = 0.0f;					// �Q�[�W�̍ŏ�
	};
	GaugeStatus		m_circleGauge;						// �~�`�Q�[�W�̃X�e�[�^�X
};

