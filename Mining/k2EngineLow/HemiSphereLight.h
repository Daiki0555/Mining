#pragma once
namespace nsK2EngineLow
{
	class HemiSphereLight
	{
	public:
		/// <summary>
		///半球ライトの構造体
		/// </summary>
		struct hemiSphereLight
		{
			Vector3 groundColor = Vector3::Zero;		//地面の色
			float pad0 = 0.0f;
			Vector3 skyColor = Vector3::Zero;			//天球色
			float pad1 = 0.0f;
			Vector3 groundNormal = Vector3::Zero;		//地面の法線
			float pad2;
		};

		HemiSphereLight();
		~HemiSphereLight();

	public:
		/// <summary>
		/// 地面の色を設定
		/// </summary>
		/// <param name="groundColor">RGB。0.0f～1.0fの間</param>
		void SetGroundColor(const Vector3& groundColor)
		{
			m_hemiSphereLight.groundColor = groundColor;
		}

		/// <summary>
		/// 空の色を設定
		/// </summary>
		/// <param name="skyColor">RGB。0.0f～1.0fの間</param>
		void SetSkyColor(const Vector3& skyColor)
		{
			m_hemiSphereLight.skyColor = skyColor;
		}

		/// <summary>
		/// 地面の法線を設定
		/// </summary>
		/// <param name="groundNormal"></param>
		void SetGroundNormal(const Vector3& groundNormal)
		{
			m_hemiSphereLight.groundNormal = groundNormal;
		}

		/// <summary>
		/// 構造体を取得
		/// </summary>
		/// <returns></returns>
		hemiSphereLight& GetHemiSphereLig()
		{
			return m_hemiSphereLight;
		}

	private:
		hemiSphereLight m_hemiSphereLight;
	};
}


