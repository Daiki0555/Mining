#pragma once
namespace nsK2EngineLow {
	class DirectionLight
	{
	public:
		struct directionLight
		{
			Vector3 ligDirection=Vector3::Zero;		//ライトの方向
			float pad0 = 0.0f;
			Vector3 ligColor= Vector3::Zero;	    //ライトのカラー
			float pad1 = 0.0f;
			Vector3 eyePos = Vector3::Zero;			//視点の位置
			float pad2 = 0.0f;
			Vector3 ambient = Vector3::Zero;		//環境光
			float pad3 = 0.0f;
		};

		DirectionLight();
		~DirectionLight();
		/// <summary>
		/// ライトの方向の設定
		/// </summary>
		void SetDirection(const Vector3 dir)
		{
			m_directionLig.ligDirection = dir;
			//ライトを正規化
			m_directionLig.ligDirection.Normalize();
		}

		/// <summary>
		/// ライトの色を設定
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
			//視点の位置を設定する
			m_directionLig.eyePos = g_camera3D->GetPosition();
		}

		/// <summary>
		/// 構造体の取得
		/// </summary>
		directionLight& GetDirectionLig()
		{
			return m_directionLig;
		}

	private:
		directionLight m_directionLig;
	};

}

