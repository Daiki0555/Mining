#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {

	namespace
	{
		const Vector3 SHADOW_CAMERA_POS = Vector3(1024.0f, 100.0f, 1024.0f);
		const Vector3 SHADOW_CAMERA_TAR = Vector3(0.0f, -100.0f, 0.0f);
	}

	RenderingEngine* RenderingEngine::m_instance = nullptr;
	RenderingEngine::RenderingEngine()
	{
		
	}

	RenderingEngine::~RenderingEngine()
	{

	}

	void RenderingEngine::Init()
	{
		InitMainRenderTarget();
	
		InitLight();

		InitShadowMapRenderTarget();
		
		Init2DRenderTarget();
		
		InitGBffer();
		
	

	}

	void RenderingEngine::InitMainRenderTarget()
	{
		//メインレンダーターゲットを設定
		float clearColor[4] = { 0.5f,0.5f,0.5f,1.0f };
		m_mainRenderTarget.Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);
	}


	void RenderingEngine::InitLight()
	{
		//ディレクションライトの設定
		SetDirectionLight(Vector3(1, -1, 1), Vector3(0.5f, 0.5f, 0.5f));

		//環境光の設定
		SetAmbient(0.7f);

		//半球ライトの設定
		/*SetHemiSphereLight(
			Vector3(1.0f, 0.5f, 0.3f),
			Vector3(0.15f, 0.7f, 0.95f),
			Vector3(0.0f, 1.0f, 0.0f)
		);*/
		//ディレクショナルライトの取得
		m_lightCB.directionLig = m_directionLig.GetDirectionLig();

		//ブルームの設定
		SetBloomThreshold(0.2f);
		m_bloom.Init(m_mainRenderTarget);

	}


	void RenderingEngine::Init2DRenderTarget()
	{
		float clearColor[4] = { 0.0f,0.0f,0.0f,0.0f };
		
		m_2DRenderTarget.Create(
			UI_SPACE_WIDTH,
			UI_SPACE_HEIGHT,
			1,
			1,
			DXGI_FORMAT_B8G8R8A8_UNORM,
			DXGI_FORMAT_UNKNOWN,
			clearColor
		);

		
	}

	void RenderingEngine::InitShadowMapRenderTarget()
	{
		//カメラの位置これはライトの位置
		m_lightCamera.SetPosition(g_camera3D->GetTarget() + Vector3(0,600,0));

		//カメラの注視点を設定。これがライトを照らしている場所
		m_lightCamera.SetTarget(g_camera3D->GetTarget());

		//上方向を設定
		m_lightCamera.SetUp(0, 1, 0);

		m_lightCamera.SetFar(5000.0f);

		//画角を設定する
		//m_lightCamera.SetViewAngle(Math::DegToRad(20.0f));
		//m_lightCamera.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);
		m_lightCamera.Update();

		//ライトビュープロテクションを行列に計算している
		m_lightCB.shadowCB.mLVP = m_lightCamera.GetViewProjectionMatrix();	

		//シャドウマップ用のレンダリングターゲットを初期化
		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
		m_shadowMapRenderTarget.Create(
			1500,
			1500,
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);


	}

	void RenderingEngine::InitGBffer()
	{
		//アルベドカラー用のレンダーターゲット
		float clearColor[4] = { 0.5f,0.5f,0.5f,1.0f };
		m_gBuffer[enGBuffer_Albedo].Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
		//法線書き込み用のレンダーターゲット
		m_gBuffer[enGBuffer_Normal].Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1, 1,
			DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_UNKNOWN
		);
		//ピクセルのワールド座標を記録するためのG-Bufferを作成
		m_gBuffer[enGBuffer_WorldPos].Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1, 1,
			DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_UNKNOWN
		);

		//金属度と滑らかさマップ出力用のレンダーターゲットを初期化
		m_gBuffer[enGBuffer_MetalSmooth].Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM, //メモリ使用量メモリ書き込み速度優先で、8bitの符号なし整数バッファを使用する。。
			DXGI_FORMAT_UNKNOWN
		);

		//影のパラメータを出力用のレンダリングターゲットを初期化
		m_gBuffer[enGBuffer_ShadowParam].Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT
		);

		//ディファードライティングを行うためのスプライトを初期化する
		//画面全体にレンダリングするので幅と高さはフレームバッファーの幅と高さと同じ
		m_deferredSpriteInitData.m_width = FRAME_BUFFER_W;
		m_deferredSpriteInitData.m_height = FRAME_BUFFER_H;

		//使用するテクスチャはアルベドテクスチャと法線テクスチャ
		m_deferredSpriteInitData.m_textures[0] = &m_gBuffer[enGBuffer_Albedo].GetRenderTargetTexture();
		m_deferredSpriteInitData.m_textures[1] = &m_gBuffer[enGBuffer_Normal].GetRenderTargetTexture();
		m_deferredSpriteInitData.m_textures[2] = &m_gBuffer[enGBuffer_WorldPos].GetRenderTargetTexture();
		m_deferredSpriteInitData.m_textures[3] = &m_gBuffer[enGBuffer_MetalSmooth].GetRenderTargetTexture();
		m_deferredSpriteInitData.m_textures[4] = &m_gBuffer[enGBuffer_ShadowParam].GetRenderTargetTexture();
		m_deferredSpriteInitData.m_textures[5] = &m_shadowMapRenderTarget.GetRenderTargetTexture();
		m_deferredSpriteInitData.m_fxFilePath = "Assets/shader/deferredLighting.fx";
		m_deferredSpriteInitData.m_expandConstantBuffer = &GetLightCB();
		m_deferredSpriteInitData.m_expandConstantBufferSize = sizeof(GetLightCB());

		//m_deferredSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		//初期化データを使ってスプライトを作成
		m_defferedLightInSpr.Init(m_deferredSpriteInitData);
	}

	void RenderingEngine::Execute(RenderContext& rc)
	{
		//シャドウマップの描画。
		RenderShadowMap(rc);	

		//ディファードレンダリング
		DefferedRender(rc);

		//ブルームの描画。
		m_bloom.Render(rc, m_mainRenderTarget);

		//2Dスプライトの描画。
		Render2D(rc);

	

		m_renderObjects.clear();
	}

	//モデルリストに入れられたモデルを描画する
	void RenderingEngine::DefferedRender(RenderContext& rc)
	{

		RenderTarget* rts[] = {
			&m_gBuffer[enGBuffer_Albedo],
			&m_gBuffer[enGBuffer_Normal],
			&m_gBuffer[enGBuffer_WorldPos],
			&m_gBuffer[enGBuffer_MetalSmooth],
			&m_gBuffer[enGBuffer_ShadowParam]
		};
		rc.WaitUntilToPossibleSetRenderTargets(ARRAYSIZE(rts),rts);
		rc.SetRenderTargetsAndViewport(ARRAYSIZE(rts),rts);
		rc.ClearRenderTargetViews(ARRAYSIZE(rts),rts);

		for (auto& modelobj : m_renderObjects){
			modelobj->OnRenderModel(rc);
		}
		
		rc.WaitUntilFinishDrawingToRenderTargets(ARRAYSIZE(rts),rts);

		//レンダリング先をフレームバッファーに戻してスプライトをレンダリングする
		g_graphicsEngine->ChangeRenderTargetToFrameBuffer(rc);

		//G-Bufferの内容をもとにスプライトをレンダリングする
		//m_defferedLightInSpr.Draw(rc);
	}

	void RenderingEngine::RenderShadowMap(RenderContext& rc)
	{

		//カメラの位置これはライトの位置
		m_lightCamera.SetPosition(g_camera3D->GetTarget() + Vector3(200,600,300) * 1.0f);
		//カメラの注視点を設定。これがライトを照らしている場所
		m_lightCamera.SetTarget(g_camera3D->GetTarget());
		m_lightCamera.Update();
		

		m_lightCB.shadowCB.mLVP = m_lightCamera.GetViewProjectionMatrix();
		m_lightCB.shadowCB.lightPos = m_lightCamera.GetPosition();
		

		//シャドウマップ用のレンダリングターゲットの書き込み待ち
		rc.WaitUntilToPossibleSetRenderTarget(m_shadowMapRenderTarget);
		rc.SetRenderTargetAndViewport(m_shadowMapRenderTarget);
		rc.ClearRenderTargetView(m_shadowMapRenderTarget);

		//描画処理
		for (auto& shadowMaps : m_renderObjects){
			shadowMaps->OnRenderShadowMap(rc,m_lightCamera);
		}

		rc.WaitUntilFinishDrawingToRenderTarget(m_shadowMapRenderTarget);
	}


	void RenderingEngine::Render2D(RenderContext& rc)
	{
		////レンダリングターゲット書き込み待ち。
		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);
		rc.SetRenderTargetAndViewport(m_mainRenderTarget);
		rc.ClearRenderTargetView(m_mainRenderTarget);
		
		m_defferedLightInSpr.Draw(rc);
		
		//描画処理
		for (auto& sprites : m_renderObjects){
			sprites->OnRender2D(rc);
		}
		
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);

	}
}
