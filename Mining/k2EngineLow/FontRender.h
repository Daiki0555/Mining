#pragma once
namespace nsK2EngineLow {

	/// <summary>
	/// �t�H���g�����_�[�N���X
	/// </summary>
	class FontRender
	{
	public:
		static const int MAX_TEXT_SIZE = 256;	//�����̍āX��

		~FontRender()
		{

		}
		/// <summary>
		/// �\�����镶���̐ݒ�
		/// </summary>
		/// <param name="text"></param>
		void SetText(const wchar_t* text)
		{
			swprintf_s(m_text, text);
		}

		/// <summary>
		/// �\�����镶�����擾
		/// </summary>
		/// <returns></returns>
		const wchar_t* GetText()
		{
			return m_text;
		}
		/// <summary>
		/// ���W�̐ݒ�Bz��0.0f
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// ���W�̎擾
		/// </summary>
		/// <returns></returns>
		const Vector3& GetPosition()
		{
			return m_position;
		}
		/// <summary>
		/// �傫����ݒ�
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(const float scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// �傫���̎擾
		/// </summary>
		/// <returns></returns>
		const float GetScale()
		{
			return m_scale;
		}
		/// <summary>
		/// �F�̐ݒ�
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const Vector4& color)
		{
			m_color = color;
		}



	private:
		Font		m_font;								//�t�H���g
		Vector2		m_pivot = Sprite::DEFAULT_PIVOT;	//�s�{�b�g
		Vector3		m_position=Vector3::Zero;			//���W
		Vector4		m_color = g_vec4White;				//�F
		wchar_t		m_text[MAX_TEXT_SIZE];				//����		
		float		m_scale = 1.0f;						//�傫��
		float		m_rotaition = 0.0f;					//��]

	};



}

