#pragma once
namespace nsK2EngineLow {
	namespace
	{
		const int POINTLIGHT_NUM = 2;		//ポイントライトの数
		const int SPOTLIGHT_NUM = 1;		//スポットライトの数
	}
	class RenderingEngine:public Noncopyable
	{
	public:

		struct ShadowParamCB
		{
			Vector3 lightPos = Vector3::Zero;
			float pad0=0.0f;
			Matrix mLVP = g_matIdentity;
		};

		//ライトの構造体
		struct LightCB
		{
			DirectionLight::directionLight directionLig;
			PointLight::pointLight pointLig[POINTLIGHT_NUM];
			SpotLight::spotLight spotLig[SPOTLIGHT_NUM];
			HemiSphereLight::hemiSphereLight hemiSphereLig;
			ShadowParamCB shadowCB;
			int ptNum;										//ポイントライトの数
			int spNum;										//スポットライトの数
		
		};

		RenderingEngine();
		~RenderingEngine();

		

	public:

		/// <summary>
		/// インスタンスの生成
		/// </summary>
		static void CreateInstance()
		{
			if (m_instance != nullptr)
			{
				std::abort();
			}
			m_instance = new RenderingEngine;
			m_instance->Init();			
		}
		/// <summary>
		/// インスタンスの削除
		/// </summary>
		static void DeleteInstance()
		{
			delete m_instance;
			m_instance = nullptr;
		}
		/// <summary>
		/// インスタンスの取得
		/// </summary>
		/// <returns></returns>
		static RenderingEngine* GetInstance()
		{
			if (m_instance == nullptr) {
				CreateInstance();
			}

			return m_instance;
		}
		
		/// <summary>
		/// レンダーオブジェクトを追加
		/// </summary>
		/// <param name="renderObject"></param>
		void AddRenderObject(IRenderer* renderObject)
		{
			m_renderObjects.emplace_back(renderObject);
		}

		/// <summary>
		/// ライト用の構造体を取得
		/// </summary>
		/// <returns></returns>
		LightCB& GetLightCB()
		{
			return m_lightCB;
		}

		/// <summary>
		/// シャドウ用の構造体を取得
		/// </summary>
		/// <returns></returns>
		ShadowParamCB& GetShadowParamCB()
		{
			return m_lightCB.shadowCB;
		}

		/// <summary>
		/// ディレクショナルライトの設定。
		/// </summary>
		/// <param name="dir">ライトの方向。</param>
		/// <param name="color">ライトのカラー。[</param>
		void SetDirectionLight(const Vector3& dir, const Vector3 color)
		{
			m_directionLig.SetDirection(dir);
			m_directionLig.SetColor(color);
			GetLightCB().directionLig = m_directionLig.GetDirectionLig();
		}

		/// <summary>
		/// 環境光の設定
		/// </summary>
		/// <param name="amb">環境光の強さ</param>
		void SetAmbient(const float amb)
		{
			m_directionLig.SetAmbientLight(amb);
			GetLightCB().directionLig = m_directionLig.GetDirectionLig();
		}

		/// <summary>
		/// ポイントライトの設定
		/// </summary>
		/// <param name="ptNum">ポイントライトの数</param>
		/// <param name="ptlig">ポイントライトの構造体</param>
		void SetPointLight(const int ptNum, PointLight::pointLight& ptlig)
		{
			GetLightCB().pointLig[ptNum].ptPosition = ptlig.ptPosition;
			GetLightCB().pointLig[ptNum].ptColor = ptlig.ptColor;
			GetLightCB().pointLig[ptNum].ptRange = ptlig.ptRange;
		}

		/// <summary>
		/// スポットライトの設定
		/// </summary>
		/// <param name="spNum">スポットライトの数</param>
		/// <param name="splig">スポットライトの構造体</param>
		void SetSpotLight(const int spNum, SpotLight::spotLight& splig)
		{
			GetLightCB().spotLig[spNum].spPosition = splig.spPosition;
			GetLightCB().spotLig[spNum].spColor = splig.spColor;
			GetLightCB().spotLig[spNum].spRange = splig.spRange;
			GetLightCB().spotLig[spNum].spDirection = splig.spDirection;
			GetLightCB().spotLig[spNum].spAngle = splig.spAngle;
		}

		/// <summary>
		/// 半球ライトを設定。
		/// </summary>
		void SetHemiSphereLight(const Vector3& grdColor, const Vector3& skyColor, const Vector3& grdNormal)
		{
			m_hemiShereLig.SetGroundColor(grdColor);
			m_hemiShereLig.SetSkyColor(skyColor);
			m_hemiShereLig.SetGroundNormal(grdNormal);
			GetLightCB().hemiSphereLig = m_hemiShereLig.GetHemiSphereLig();
		}

		/// <summary>
		/// ブルームの閾値を設定
		/// </summary>
		/// <param name="threshold">閾値</param>
		void SetBloomThreshold(const float threshold)
		{
			m_bloom.SetThreshold(threshold);
		}

		/// <summary>
		/// シャドウマップのレンダリングターゲットを取得
		/// </summary>
		/// <returns></returns>
		RenderTarget& GetShadowMapRenderTarget()
		{
			return m_shadowMapRenderTarget;
		}


		/// <summary>
		/// 初期化処理
		/// </summary>
		void Init();

		/// <summary>
		/// 実行処理
		/// </summary>
		/// <param name="rc"></param>
		void Execute(RenderContext& rc);
	private:
		/// <summary>
		/// ライトの初期化
		/// </summary>
		void InitLight();

		/// <summary>
		/// メインレンダリングターゲットを初期化
		/// </summary>
		void InitMainRenderTarget();

		/// <summary>
		/// シャドウマップ用のレンダーターゲットを初期化。
		/// </summary>
		void InitShadowMapRenderTarget();

		/// <summary>
		/// 2Dレンダーターゲットを初期化
		/// </summary>
		void Init2DRenderTarget();

		/// <summary>
		///G-Bufferの初期化
		/// </summary>
		void InitGBffer();


		/// <summary>
		/// ディファードライティング
		/// </summary>
		/// <param name="rc"></param>
		void DefferedRender(RenderContext& rc);

		/// <summary>
		/// シャドウマップの描画処理
		/// </summary>
		/// <param name="rc"></param>
		void RenderShadowMap(RenderContext& rc);

		/// <summary>
		/// 2D描画処理
		/// </summary>
		/// <param name="rc"></param>
		void Render2D(RenderContext& rc);

	private:
		//GBufferの定義
		enum EnGBffer
		{
			enGBuffer_Albedo,			//アルベド
			enGBuffer_Normal,			//法線
			enGBuffer_WorldPos,			//ワールド座標
			enGBuffer_MetalSmooth,		//金属度と滑らかさ。xに金属度、wに滑らかさが記録されている。
			enGBuffer_ShadowParam,		//影のパラメータ
			enGBuffer_Num,				//GBufferの数
		};

		static RenderingEngine*		m_instance;							//ライト用の構造体
		
		DirectionLight				m_directionLig;						//ディレクショナルライトの構造体
		LightCB						m_lightCB;
		HemiSphereLight				m_hemiShereLig;
		Bloom						m_bloom;							//ブルーム
		


		RenderTarget				m_mainRenderTarget;					//メインレンダーターゲット
		RenderTarget				m_2DRenderTarget;					//2Dレンダーターゲット
		RenderTarget				m_shadowMapRenderTarget;
		RenderTarget			    m_gBuffer[enGBuffer_Num];			//G-Buffer
		
		Sprite						m_2DSprite;							//2Dスプライト
		Sprite						m_mainSprite;
		Sprite						m_defferedLightInSpr;				//ディファードライティング用のスプライト

		SpriteInitData				m_deferredSpriteInitData;			//ディファードライティングを行うためのスプライトの初期化
		
										
		Camera						m_lightCamera;						//描画用のライトカメラを作成する



		std::vector<IRenderer*>		m_renderObjects;					//


	};
}


