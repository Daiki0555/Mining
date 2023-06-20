#pragma once
class GaugeBasic:public IGameObject
{
public:
	GaugeBasic();
	~GaugeBasic();

	bool Start(int value);
	void DrawGaugeValue(int value);
	void ChangeGaugeValue(int value);

	enum enGaugeState {
		enGaugeState_IncreaseStart,			// �Q�[�W�����J�n
		enGaugeState_IncreaseEnd,			// �Q�[�W�����I��
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
	enGaugeState	m_enGaugeState;			// �X�e�[�g

	SpriteRender	m_spriteRender;			// �X�v���C�g�����_�[
	FontRender		m_fontRender;			// �t�H���g�����_�[

	int				m_gaugeMaxValue = 0;	// �ő�l
	int				m_gaugeMinValue = 0;	// �ŏ��l
	int				m_gaugeNowValue = 0;	// ���݂̒l
};

