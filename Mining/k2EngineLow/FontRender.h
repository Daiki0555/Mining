#pragma once
namespace nsK2EngineLow {

	/// <summary>
	/// フォントレンダークラス
	/// </summary>
	class FontRender
	{
	public:
		static const int MAX_TEXT_SIZE = 256;	//文字の再々数

		~FontRender()
		{

		}
		/// <summary>
		/// 表示する文字の設定
		/// </summary>
		/// <param name="text"></param>
		void SetText(const wchar_t* text)
		{
			swprintf_s(m_text, text);
		}

		/// <summary>
		/// 表示する文字を取得
		/// </summary>
		/// <returns></returns>
		const wchar_t* GetText()
		{
			return m_text;
		}
		/// <summary>
		/// 座標の設定。zは0.0f
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// 座標の取得
		/// </summary>
		/// <returns></returns>
		const Vector3& GetPosition()
		{
			return m_position;
		}
		/// <summary>
		/// 大きさを設定
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(const float scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// 大きさの取得
		/// </summary>
		/// <returns></returns>
		const float GetScale()
		{
			return m_scale;
		}
		/// <summary>
		/// 色の設定
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const Vector4& color)
		{
			m_color = color;
		}



	private:
		Font		m_font;								//フォント
		Vector2		m_pivot = Sprite::DEFAULT_PIVOT;	//ピボット
		Vector3		m_position=Vector3::Zero;			//座標
		Vector4		m_color = g_vec4White;				//色
		wchar_t		m_text[MAX_TEXT_SIZE];				//文字		
		float		m_scale = 1.0f;						//大きさ
		float		m_rotaition = 0.0f;					//回転

	};



}

