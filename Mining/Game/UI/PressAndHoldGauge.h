#pragma once

namespace 
{
	const float		CIRCLE_SIZE_MAX = 0.0f;								// �~�`�Q�[�W�̍ő�
	const float		CIRCLE_SIZE_MIN = 360.0f;							// �~�`�Q�[�W�̍ŏ�
}

class PressAndHoldGauge:public IGameObject
{
public:
	PressAndHoldGauge();
	~PressAndHoldGauge();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// �Q�[�W�̊p�x��ύX
	/// </summary>
	void ChangeGaugeAngle();
	/// <summary>
	/// �Q�[�W�̍��W��ύX
	/// </summary>
	void ChangeGaugePosition();
	/// <summary>
	/// �t�H���g�����_�[�̕\��
	/// </summary>
	void SetFontRender();
	/// <summary>
	/// �p�x�̃��Z�b�g
	/// </summary>
	void ResetGaugeAngle() {
		// �X�e�[�^�X���Đݒ�
		m_circleGauge.m_angle = CIRCLE_SIZE_MAX;
	};

	/// <summary>
	/// �`�悷�邩�ǂ����̃t���O��ݒ肷��
	/// </summary>
	/// <param name="flag">true�Ȃ�`��</param>
	void SetCanDrawGauge(bool flag) {
		m_canDrawGaugeFlag = flag;
	}

	/// <summary>
	/// �p�x��ύX���邩�ǂ����̃t���O��ݒ肷��
	/// </summary>
	/// <param name="flag">true�Ȃ猸��������</param>
	void SetChangeGaugeAngle(bool flag) {
		m_changeGaugeAngleFlag = flag;
	}

	/// <summary>
	/// ���W��ݒ肷��
	/// </summary>
	/// <param name="position">3D���W</param>
	void Set3DPosition(Vector3 position) {
		m_circleGauge.m_3Dposition = position;
	}

	enum enGaugeState {
		enGaugeState_Max,								// �Q�[�W�ő�
		enGaugeState_Min,								// �Q�[�W�ŏ�
		enGaugeState_Increase,							// �Q�[�W������
		enGaugeState_Decrease							// �Q�[�W������
	};

	/// <summary>
	/// ���݂̃X�e�[�g���擾����
	/// </summary>
	/// <returns></returns>
	const enGaugeState GetNowStatus() const {
		return m_enGaugeState;
	}

private:
	SpriteRender	m_spriteRenderCircle;				// �X�v���C�g�����_�[
	SpriteRender	m_spriteRenderCircleBase;			// �X�v���C�g�����_�[(�x�[�X)
	SpriteRender	m_spriteRenderCircleBack;			// �X�v���C�g�����_�[(�w�i)
	
	FontRender		m_fontRender;						// �t�H���g�����_�[

	struct GaugeStatus {
		Vector3		m_3Dposition = Vector3::Zero;		// 3D���W
		Vector2		m_2Dposition = Vector2::Zero;		// 2D���W
		float		m_angle = CIRCLE_SIZE_MAX;			// �Q�[�W�̊p�x(�����l)
		float		m_maxSize = CIRCLE_SIZE_MAX;		// �Q�[�W�̍ő�
		float		m_minSize = CIRCLE_SIZE_MIN;		// �Q�[�W�̍ŏ�
	};
	GaugeStatus		m_circleGauge;						// �~�`�Q�[�W�̃X�e�[�^�X

	enGaugeState	m_enGaugeState = enGaugeState_Max;	// �Q�[�W�̍��̃X�e�[�g

	bool			m_changeGaugeAngleFlag = false;		// true�Ȃ瑝���Afalse�Ȃ猸��������
	bool			m_canDrawGaugeFlag = false;			// �`��ł��邩�ǂ���
};