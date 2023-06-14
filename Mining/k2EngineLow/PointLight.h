#pragma once
namespace nsK2EngineLow {
	/// <summary>
	/// ポイントライト
	/// </summary>
	class PointLight
	{
	public:
		/// <summary>
		/// ポイントライト用の構造体
		/// </summary>
		struct pointLight
		{
			Vector3 ptPosition;			//座標
			float pad = 0.0f;
			Vector3 ptColor;			//カラー
			float ptRange=0.0f;			//影響範囲
		};

		PointLight();
		~PointLight();

		/// <summary>
		/// ポイントライトの設定
		/// </summary>
		/// <param name="num">番号</param>
		/// <param name="pos">座標</param>
		/// <param name="color">カラー</param>
		/// <param name="range">影響範囲</param>
		void SetPointLight(const int num, const Vector3& pos, const Vector3 color, const float range)
		{
			SetNumber(num);
			SetPosition(pos);
			SetColor(color);
			SetRange(range);
			Update();
		}

		/// <summary>
		/// ポイントライトの番号を設定
		/// </summary>
		void SetNumber(const int num)
		{
			m_ptNum = num;
		}

		/// <summary>
		/// ポイントライトの座標の設定
		/// </summary>
		/// <param name="pos">座標</param>
		void SetPosition(const Vector3& pos)
		{
			m_pointLig.ptPosition = pos;

		}

		/// <summary>
		/// 座標の取得
		/// </summary>
		/// <returns></returns>
		const Vector3& GetPosition()
		{
			return m_pointLig.ptPosition;
		}

		/// <summary>
		/// カラーの設定
		/// </summary>
		/// <param name="color">カラー</param>
		void SetColor(const Vector3& color)
		{
			m_pointLig.ptColor = color;
		}

		/// <summary>
		/// カラーの取得
		/// </summary>
		/// <returns></returns>
		const Vector3 GetColor()
		{
			return m_pointLig.ptColor;
		}


		/// <summary>
		/// 影響範囲の設定
		/// </summary>
		/// <param name="range"></param>
		void SetRange(float range)
		{
			m_pointLig.ptRange = range;
		}

		/// <summary>
		/// 影響範囲を取得。
		/// </summary>
		const float& GetRange()
		{
			return m_pointLig.ptRange;
		}

		/// <summary>
		/// 構造体を取得
		/// </summary>
		/// <returns></returns>
		const pointLight& GetPointLig()
		{
			return m_pointLig;
		}

		/// <summary>
		/// 更新処理
		/// </summary>
		void Update();
	private:
		pointLight		m_pointLig;			//ポイントライトの構造体
		int				m_ptNum = 0;		//ポイントライトの番号
	};
}
