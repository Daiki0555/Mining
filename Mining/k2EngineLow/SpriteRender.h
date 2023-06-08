#pragma once
namespace nsK2EngineLow {
	class SpriteRender
	{
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X</param>
		/// <param name="w">�摜�̉���</param>
		/// <param name="h">�摜�̏c��</param>
		/// <param name="alphaBlendMode">�f�t�H���g�͔�����</param>
		void Init(
			const char* filePath,
			const float w,
			const float h,
			AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans
		);

		/// <summary>
		/// ���W��ݒ�Bz��0.0f
		/// </summary>
		/// <param name="pos">���W�iz��0.0f�j</param>
		/// <returns></returns>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// ���W���擾
		/// </summary>
		/// <returns>���W</returns>
		const Vector3& GetPosition()const
		{
			return m_position;
		}
		/// <summary>
		/// �傫����ݒ�Bz��1.0f
		/// </summary>
		/// <param name="scale">�傫��</param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// �傫�����擾
		/// </summary>
		/// <returns></returns>
		const Vector3 GetScale()const
		{
			return m_scale;
		}
		/// <summary>
		/// ��]�̐ݒ�
		/// </summary>
		/// <param name="rot">��]</param>
		void SetRotation(const Quaternion& rot)
		{
			m_rotaition = rot;
		}
		/// <summary>
		/// ��]���擾
		/// </summary>
		/// <returns>��]</returns>
		const Quaternion& GetRotation()const
		{
			return m_rotaition;
		}
		/// <summary>
		/// �s�{�b�g��ݒ�
		/// </summary>
		/// <param name="pivot">�s�{�b�g</param>
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}
		/// <summary>
		/// �s�{�b�g���擾
		/// </summary>
		/// <returns></returns>
		const Vector2 GetPivot()const
		{
			return m_pivot;
		}
		/// <summary>
		/// ��Z�J���[��ݒ�
		/// </summary>
		/// <param name="mulColor">��Z�J���[</param>
		void SetMulColor(const Vector4& mulColor)
		{
			m_sprite.SetMulColor(mulColor);
		}
		/// <summary>
		/// ��Z�J���[���擾
		/// </summary>
		/// <returns></returns>
		const Vector4& GetMulColor()const
		{
			return m_sprite.GetMulColor();
		}

		/// <summary>
		/// �X�V����
		/// </summary>
		void Update()
		{
			m_sprite.Update(
				m_position,
				m_rotaition,
				m_scale,
				m_pivot
			);
		}
		/// <summary>
		/// �`�揈��
		/// </summary>
		/// <param name="rc">�����_�[�R���e�L�X�g</param>
		void Draw(RenderContext& rc);

		void OnRender2D(RenderContext& rc)
		{
			m_sprite.Draw(rc);
		}
	private:
		
	private:
		Sprite			m_sprite;
		Vector3			m_position = Vector3::Zero;
		Vector3			m_scale = Vector3::Zero;
		Quaternion		m_rotaition = Quaternion::Identity;
		Vector2			m_pivot = Sprite::DEFAULT_PIVOT;
	};

}

