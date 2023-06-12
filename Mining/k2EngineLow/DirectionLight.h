#pragma once
namespace nsK2EngineLow {
	class DirectionLight
	{
	public:
		struct directionLight
		{
			Vector3 ligDirection=Vector3::Zero;		//���C�g�̕���
			float pad0 = 0.0f;
			Vector3 ligColor= Vector3::Zero;	    //���C�g�̃J���[
			float pad1 = 0.0f;
			Vector3 eyePos = Vector3::Zero;			//���_�̈ʒu
			float pad2 = 0.0f;
			Vector3 ambient = Vector3::Zero;		//����
			float pad3 = 0.0f;
		};

		DirectionLight();
		~DirectionLight();
		/// <summary>
		/// ���C�g�̕����̐ݒ�
		/// </summary>
		void SetDirection(const Vector3 dir)
		{
			m_directionLig.ligDirection = dir;
			//���C�g�𐳋K��
			m_directionLig.ligDirection.Normalize();
		}

		/// <summary>
		/// ���C�g�̐F��ݒ�
		/// </summary>
		void SetColor(const Vector3 color)
		{
			m_directionLig.ligColor = color;
		}


		void SetAmbientLight(const float amb)
		{
			m_directionLig.ambient.x = amb;
			m_directionLig.ambient.y = amb;
			m_directionLig.ambient.z = amb;
		}

		void SeteyePos()
		{
			//���_�̈ʒu��ݒ肷��
			m_directionLig.eyePos = g_camera3D->GetPosition();
		}

		/// <summary>
		/// �\���̂̎擾
		/// </summary>
		directionLight& GetDirectionLig()
		{
			return m_directionLig;
		}

	private:
		directionLight m_directionLig;
	};

}

