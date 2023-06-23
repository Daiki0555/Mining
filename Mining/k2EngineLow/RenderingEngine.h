#pragma once

namespace nsK2EngineLow {
	class ModelRender;
	class SpriteRender;
	class RenderTarget;
	class FontRender;
	class DirectionLight;
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
			PointLight::pointLight pointLig[2];
			SpotLight::spotLight spotLig[1];
			HemiSphereLight::hemiSphereLight hemiSphereLig;
			ShadowParamCB shadowCB;
			int ptNum;										//ポイントライトの数
			int spNum;										//スポットライトの数
		
		};

		// スプライト用の構造体
		struct SpriteCB
		{
			float angle;
		};

	//private:
		RenderingEngine();
		~RenderingEngine();

		

	public:

		/// <summary>
		/// インスタンスの生成
		/// </summary>
		static void CreateInstance()
		{
			m_instance = new RenderingEngine;
			m_instance->Init();
		}
		/// <summary>
		/// インスタンスの削除
		/// </summary>
		static void DeleteInstance()
		{
			delete m_instance;
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
		/// レンダーオブジェクトを追加
		/// </summary>
		/// <param name="renderObject"></param>
		void AddModelRenderObject(ModelRender* renderObject)
		{
			m_modeList.emplace_back(renderObject);
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
		/// スプライト用の構造体を取得
		/// </summary>
		/// <returns></returns>
		SpriteCB& GetSpriteCB()
		{
			return m_spiteCB;
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
		/// モデルの描画
		/// </summary>
		/// <param name="rc"></param>
		void ModelRendering(RenderContext& rc);

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
		static RenderingEngine*		m_instance;							//ライト用の構造体
		
		DirectionLight				m_directionLig;						//ディレクショナルライトの構造体
		LightCB						m_lightCB;
		SpriteCB					m_spiteCB;							//スプライト用の構造体
		HemiSphereLight				m_hemiShereLig;
		Bloom						m_bloom;							//ブルーム
		


		RenderTarget				m_mainRenderTarget;					//メインレンダーターゲット
		RenderTarget				m_2DRenderTarget;					//2Dレンダーターゲット
		RenderTarget				m_shadowMapRenderTarget;
		
		Sprite						m_2DSprite;							//2Dスプライト
		Sprite						m_mainSprite;
		Sprite sprite;
		
										
		Camera						m_lightCamera;						//描画用のライトカメラを作成する



		std::vector<SpriteRender*>  m_spriteList;						//レンダリングするオブジェクト
		std::vector<ModelRender*>	m_modeList;							//モデルリスト
		std::vector<FontRender*>	m_fontList;							//フォントリスト
		std::vector<IRenderer*>		m_renderObjects;


	};
}


