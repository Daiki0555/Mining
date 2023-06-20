#include "stdafx.h"
#include "GaugeBasic.h"

namespace
{
	const Vector3		FONT_POSITION = { 0.0f,0.0f,0.0f };				// �t�H���g�̍��W
	const float			FONT_SCALE = 1.0f;								// �t�H���g�̃X�P�[��
	const float			FONT_SHADOW_OFFSET = 2.0f;						// �s�N�Z���̃I�t�Z�b�g��
	const Vector4		FONT_SHADOW_COLOR = { 1.0f,1.0f,1.0f,1.0f };	// �J���[
}

GaugeBasic::GaugeBasic()
{
}

GaugeBasic::~GaugeBasic()
{
}

bool GaugeBasic::Start(int value)
{
	m_gaugeMaxValue = value;		// �ő�l��ݒ�
	m_gaugeNowValue = value;		// ���݂̒l��ݒ肷��

	return true;
}

void GaugeBasic::DrawGaugeValue(int value)
{
	m_gaugeNowValue -= value;

	// ���݂̎c��̗́EHP��\������
	wchar_t text[256];
	// �����̎w��
	swprintf_s(text, 256, L"%d / %d", m_gaugeNowValue,m_gaugeMaxValue);

	m_fontRender.SetText(text);
	m_fontRender.SetPosition(FONT_POSITION);
	m_fontRender.SetScale(FONT_SCALE);
	m_fontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);
}

void GaugeBasic::ChangeGaugeValue(int value)
{
	int sum = 0;
	int num = 1;

	if (enGaugeState_DecrementStart) {
		m_gaugeNowValue -= num;
	}
	else {
		m_gaugeNowValue += num;
	}

	sum += num;

	// sum���ݒ肵���l�ȏ�ɂȂ����Ƃ�
	if (sum >= value) {
		sum = value;

		if (enGaugeState_DecrementStart) {
			m_enGaugeState = enGaugeState_DecrementEnd;
			return;
		}
		m_enGaugeState = enGaugeState_IncreaseEnd;
	}
}
