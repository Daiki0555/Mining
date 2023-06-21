#pragma once
class Player;
class Gauge:public IGameObject
{
public:
	Gauge();
	~Gauge();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void DrawGaugeValue();

	struct GaugeStatus {
		int			m_gaugeMaxValue = 0;				// �ő�l
		int			m_gaugeMinValue = 0;				// �ŏ��l
		int			m_gaugeNowValue = 0;				// ���݂̒l
		int			m_gaugeDrawValue = 0;				// �`�掞�Ɏg�p����ϐ�
		float		m_gaugeScaleX = 0.0f;				// �Q�[�W�̃X�P�[��
	};

	void ChangeGaugeValue(GaugeStatus& gauge);

	enum enGaugeState {
		enGaugeState_IncreaseStart,			// �Q�[�W�����J�n
		enGaugeState_IncreaseEnd,			// �Q�[�W�����I��s
		enGaugeState_DecrementStart,		// �Q�[�W�����J�n
		enGaugeState_DecrementEnd			// �Q�[�W�����I��
	};

	/// <summary>
	/// �X�e�[�g��ݒ肷��
	/// </summary>
	void SetGaugeState(enGaugeState state) {
		m_enGaugeState = state;
	}

	/// <summary>
	/// ���݂̃X�e�[�g��Ԃ�
	/// </summary>s
	const enGaugeState GetGaugeState() const{
		return m_enGaugeState;
	}

private:
	SpriteRender	m_spriteRenderHitPointGauge;		// �X�v���C�g�����_�[(HP)
	SpriteRender	m_spriteRenderHitPointGaugeBase;	// �X�v���C�g�����_�[(HP)
	SpriteRender	m_spriteRenderStaminaGauge;			// �X�v���C�g�����_�[(�X�^�~�i)
	SpriteRender	m_spriteRenderStaminaGaugeBase;		// �X�v���C�g�����_�[(�X�^�~�i)
	SpriteRender	m_spriteRenderUnityChan;			// �X�v���C�g�����_�[

	FontRender		m_fontRenderHitPoint;				// �t�H���g�����_�[(HP)
	FontRender		m_fontRenderStamina;				// �t�H���g�����_�[(�X�^�~�i)

	enGaugeState	m_enGaugeState;						// �X�e�[�g

	Player*			m_player = nullptr;					// �v���C���[

	GaugeStatus		m_hitPointGauge;					// HP
	GaugeStatus		m_staminaGauge;						// �X�^�~�i
};

