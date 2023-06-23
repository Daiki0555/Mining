#include "stdafx.h"
#include "PressAndHoldGauge.h"

namespace
{
	const float		CIRCLE_SIZE_MAX = 0.0f;								// �~�`�Q�[�W�̍ő�
	const float		CIRCLE_SIZE_MIN = 360.0f;							// �~�`�Q�[�W�̍ŏ�

	const Vector3	TEX_SCALE = { 1.0f,1.0f,1.0f };						// �e�N�X�`���̃X�P�[��

	const float		DECREASE_CIRCLE_ANGLE = 36.0f;						// �p�x�̌������x
	const float		INCREASE_CIRCLE_ANGLE = 120.0f;						// �p�x�̑������x

	const float		FONT_SCALE = 0.5f;									// �t�H���g�̃X�P�[�� 
	const Vector4	FONT_COLOR = { 0.0f,0.0f,0.0f,1.0f };				// �t�H���g�̃J���[
	const float		FONT_SHADOW_OFFSET = 2.0f;							// �s�N�Z���̃I�t�Z�b�g��
	const Vector4	FONT_SHADOW_COLOR = { 1.0f,1.0f,1.0f,1.0f };		// �J���[

	const float		FONT_LEFT_X = 39.0f;								// ���Ɉړ�������l
	const float		FONT_DOWN_Y = 8.0f;									// ���Ɉړ�������l

	const float		PI = 3.14159;										// �~����
}

PressAndHoldGauge::PressAndHoldGauge()
{

}

PressAndHoldGauge::~PressAndHoldGauge()
{

}

bool PressAndHoldGauge::Start()
{
	// �X�e�[�^�X��ݒ�
	m_circleGauge.m_angle = CIRCLE_SIZE_MIN;
	m_circleGauge.m_maxSize = CIRCLE_SIZE_MAX;
	m_circleGauge.m_minSize = CIRCLE_SIZE_MIN;

	// �摜��ݒ�
	m_spriteRenderCircle.Init("Assets/Sprite/UI/Gauge/pushAndHoldGauge.DDS", 100, 100);
	m_spriteRenderCircle.SetScale(TEX_SCALE);
	m_spriteRenderCircle.Update();

	m_spriteRenderCircleBase.Init("Assets/Sprite/UI/Gauge/pushAndHoldGauge_base.DDS", 109, 109);
	m_spriteRenderCircleBase.SetScale(TEX_SCALE);
	m_spriteRenderCircleBase.Update();

	RenderingEngine::GetInstance()->GetSpriteCB().angle = (m_circleGauge.m_angle * PI) / 180.0f;

	return true;
}

void PressAndHoldGauge::Update()
{
	if (m_canDrawGaugeFlag == false) {
		return;
	}

	ChangeGaugeAngle();
	ChangeGaugePosition();
	SetFontRender();
}

void PressAndHoldGauge::ChangeGaugeAngle()
{
	// �Q�[�W�̕ύX
	if (m_changeGaugeAngleFlag) {
		// �X�e�[�g��ύX
		m_enGaugeState = enGaugeState_Increase;
		// �l�𑝉�
		m_circleGauge.m_angle -= INCREASE_CIRCLE_ANGLE * g_gameTime->GetFrameDeltaTime();
		// max�֐����g�p���čő�l���擾����
		m_circleGauge.m_angle = max(m_circleGauge.m_angle, CIRCLE_SIZE_MAX);
	}
	else{
		// �X�e�[�g��ύX
		m_enGaugeState = enGaugeState_Decrease;
		// �l������
		m_circleGauge.m_angle += DECREASE_CIRCLE_ANGLE * g_gameTime->GetFrameDeltaTime();
		// min�֐����g�p���čŏ��l���擾����
		m_circleGauge.m_angle = min(m_circleGauge.m_angle, CIRCLE_SIZE_MIN);
	}

	// ���݂̒l - �Q�[�W�̍ő�l�����ȉ��������Ƃ�
	if (m_circleGauge.m_angle < 0.0f) {
		// �Q�[�W�͍ő�
		m_enGaugeState = enGaugeState_Max;
	}
	else if(m_circleGauge.m_angle >= 360.0f) {
		// �Q�[�W�͍ő�
		m_enGaugeState = enGaugeState_Min;
	}

	// �p�x��K��
	RenderingEngine::GetInstance()->GetSpriteCB().angle = (m_circleGauge.m_angle * PI) / 180.0f;
}

void PressAndHoldGauge::ChangeGaugePosition()
{
	// �v���C���[�̍��W���Q��
	Vector3 m_worldPosition = m_circleGauge.m_3Dposition;
	// ���[���h���W����X�N���[�����W���v�Z
	g_camera3D->CalcScreenPositionFromWorldPosition(m_circleGauge.m_2Dposition, m_worldPosition);

	m_spriteRenderCircle.SetPosition({ m_circleGauge.m_2Dposition.x, m_circleGauge.m_2Dposition.y, 0.0f });
	m_spriteRenderCircle.Update();

	m_spriteRenderCircleBase.SetPosition({ m_circleGauge.m_2Dposition.x, m_circleGauge.m_2Dposition.y, 0.0f });
	m_spriteRenderCircleBase.Update();
}

void PressAndHoldGauge::SetFontRender()
{
	// �t�H���g��\������
	m_fontRender.SetText(L"B������");
	m_fontRender.SetPosition({ m_circleGauge.m_2Dposition.x - FONT_LEFT_X, m_circleGauge.m_2Dposition.y - FONT_DOWN_Y ,0.0f });
	m_fontRender.SetColor(FONT_COLOR);
	m_fontRender.SetScale(FONT_SCALE);
	m_fontRender.SetShadowParam(true, FONT_SHADOW_OFFSET, FONT_SHADOW_COLOR);
}

void PressAndHoldGauge::Render(RenderContext& rc)
{
	if (m_canDrawGaugeFlag) {
		m_spriteRenderCircle.Draw(rc);
		m_spriteRenderCircleBase.Draw(rc);
		m_fontRender.Draw(rc);
	}
}
