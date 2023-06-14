#pragma once
namespace nsK2EngineLow {
	/// <summary>
	/// �|�C���g���C�g
	/// </summary>
	class PointLight
	{
	public:
		/// <summary>
		/// �|�C���g���C�g�p�̍\����
		/// </summary>
		struct pointLight
		{
			Vector3 ptPosition;			//���W
			float pad = 0.0f;
			Vector3 ptColor;			//�J���[
			float ptRange=0.0f;			//�e���͈�
		};

		PointLight();
		~PointLight();

		/// <summary>
		/// �|�C���g���C�g�̐ݒ�
		/// </summary>
		/// <param name="num">�ԍ�</param>
		/// <param name="pos">���W</param>
		/// <param name="color">�J���[</param>
		/// <param name="range">�e���͈�</param>
		void SetPointLight(const int num, const Vector3& pos, const Vector3 color, const float range)
		{
			SetNumber(num);
			SetPosition(pos);
			SetColor(color);
			SetRange(range);
			Update();
		}

		/// <summary>
		/// �|�C���g���C�g�̔ԍ���ݒ�
		/// </summary>
		void SetNumber(const int num)
		{
			m_ptNum = num;
		}

		/// <summary>
		/// �|�C���g���C�g�̍��W�̐ݒ�
		/// </summary>
		/// <param name="pos">���W</param>
		void SetPosition(const Vector3& pos)
		{
			m_pointLig.ptPosition = pos;

		}

		/// <summary>
		/// ���W�̎擾
		/// </summary>
		/// <returns></returns>
		const Vector3& GetPosition()
		{
			return m_pointLig.ptPosition;
		}

		/// <summary>
		/// �J���[�̐ݒ�
		/// </summary>
		/// <param name="color">�J���[</param>
		void SetColor(const Vector3& color)
		{
			m_pointLig.ptColor = color;
		}

		/// <summary>
		/// �J���[�̎擾
		/// </summary>
		/// <returns></returns>
		const Vector3 GetColor()
		{
			return m_pointLig.ptColor;
		}


		/// <summary>
		/// �e���͈͂̐ݒ�
		/// </summary>
		/// <param name="range"></param>
		void SetRange(float range)
		{
			m_pointLig.ptRange = range;
		}

		/// <summary>
		/// �e���͈͂��擾�B
		/// </summary>
		const float& GetRange()
		{
			return m_pointLig.ptRange;
		}

		/// <summary>
		/// �\���̂��擾
		/// </summary>
		/// <returns></returns>
		const pointLight& GetPointLig()
		{
			return m_pointLig;
		}

		/// <summary>
		/// �X�V����
		/// </summary>
		void Update();
	private:
		pointLight		m_pointLig;			//�|�C���g���C�g�̍\����
		int				m_ptNum = 0;		//�|�C���g���C�g�̔ԍ�
	};
}
