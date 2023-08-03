#pragma once

class Player;

class PlayerStatusGauge:public IGameObject
{
public:
	PlayerStatusGauge();
	~PlayerStatusGauge();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	/// <summary>
	/// �l��\������
	/// </summary>
	void DrawGaugeValue();

	struct GaugeStatus {
		int			m_gaugeMaxValue = 0;				// �ő�l
		int			m_gaugeMinValue = 0;				// �ŏ��l
		int			m_gaugeNowValue = 0;				// ���݂̒l
		int			m_gaugeDrawValue = 0;				// �`�掞�Ɏg�p����ϐ�
		float		m_gaugeScaleX = 0.0f;				// �Q�[�W�̃X�P�[��
	};

	/// <summary>
	/// �l��ύX����
	/// </summary>
	/// <param name="gauge">�l��ύX����Q�[�W</param>
	void ChangeGaugeValue(GaugeStatus& gauge);

private:
	SpriteRender	m_spriteRenderHitPointGauge;		// �X�v���C�g�����_�[(HP)
	SpriteRender	m_spriteRenderHitPointGaugeBase;	// �X�v���C�g�����_�[(HP)
	SpriteRender	m_spriteRenderStaminaGauge;			// �X�v���C�g�����_�[(�X�^�~�i)
	SpriteRender	m_spriteRenderStaminaGaugeBase;		// �X�v���C�g�����_�[(�X�^�~�i)
	SpriteRender	m_spriteRenderUnityChan;			// �X�v���C�g�����_�[
	FontRender		m_fontRenderHitPoint;				// �t�H���g�����_�[(HP)
	FontRender		m_fontRenderStamina;				// �t�H���g�����_�[(�X�^�~�i)
	Player*			m_player = nullptr;					// �v���C���[
	GaugeStatus		m_hitPointGauge;					// HP
	GaugeStatus		m_staminaGauge;						// �X�^�~�i
};

