#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {

	namespace
	{
		const Vector3 SHADOW_CAMERA_POS = Vector3(1024.0f, 2000.0f, 1024.0f);
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
		SetAmbient(0.2f);

		//半球ライトの設定
	/*	SetHemiSphereLight(
			Vector3(1.0f, 0.5f, 0.3f),
			Vector3(0.15f, 0.7f, 0.95f),
			Vector3(0.0f, 1.0f, 0.0f)
		);*/
		//ディレクショナルライトの取得
		m_lightCB.directionLig = m_directionLig.GetDirectionLig();

		//ブルームの設定
		SetBloomThreshold(0.1f);
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

		//円形ゲージ用に一旦コメントアウト
		//最終合成用スプライトの初期化
		SpriteInitData finalSpriteInitData;
		finalSpriteInitData.m_textures[0] = &m_2DRenderTarget.GetRenderTargetTexture();
		// 解像度はmainRenderTargetの幅と高さ
		finalSpriteInitData.m_width = m_mainRenderTarget.GetWidth();
		finalSpriteInitData.m_height = m_mainRenderTarget.GetHeight();
		// 2D用のシェーダーを使用する
		finalSpriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		finalSpriteInitData.m_vsEntryPointFunc = "VSMain";
		finalSpriteInitData.m_psEntryPoinFunc = "PSMain";
		// 円形ゲージ用の構造体の情報を渡す
		finalSpriteInitData.m_expandConstantBuffer = &RenderingEngine::GetInstance()->GetSpriteCB();
		finalSpriteInitData.m_expandConstantBufferSize = sizeof(RenderingEngine::GetInstance()->GetSpriteCB());
		//上書き
		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
		//レンダリングターゲットのフォーマット
		finalSpriteInitData.m_colorBufferFormat[0] = m_mainRenderTarget.GetColorBufferFormat();
		
		m_2DSprite.Init(finalSpriteInitData);

		//2D統合用スプライトの初期化
		SpriteInitData spriteInitData;
		spriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();
		spriteInitData.m_width = m_2DRenderTarget.GetWidth();
		spriteInitData.m_height = m_2DRenderTarget.GetHeight();
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		spriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
		spriteInitData.m_colorBufferFormat[0] = m_2DRenderTarget.GetColorBufferFormat();
		
		m_mainSprite.Init(spriteInitData);

		////最終合成用スプライトの初期化
		//SpriteInitData finalSpriteInitData;
		//finalSpriteInitData.m_textures[0] = &m_2DRenderTarget.GetRenderTargetTexture();
		//// 解像度はmainRenderTargetの幅と高さ
		//finalSpriteInitData.m_width = m_mainRenderTarget.GetWidth();
		//finalSpriteInitData.m_height = m_mainRenderTarget.GetHeight();
		//// 2D用のシェーダーを使用する
		//finalSpriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		//finalSpriteInitData.m_vsEntryPointFunc = "VSMain";
		//finalSpriteInitData.m_psEntryPoinFunc = "PSMain";
		////上書き
		//finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
		////レンダリングターゲットのフォーマット
		//finalSpriteInitData.m_colorBufferFormat[0] = m_mainRenderTarget.GetColorBufferFormat();
		//
		//m_2DSprite.Init(finalSpriteInitData);

	//	//2D統合用スプライトの初期化
	//	SpriteInitData spriteInitData;
	//	spriteInitData.m_textures[0] = &m_mainRenderTarget.GetRenderTargetTexture();
	//	spriteInitData.m_width = m_2DRenderTarget.GetWidth();
	//	spriteInitData.m_height = m_2DRenderTarget.GetHeight();
	//	spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
	//	spriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
	//	spriteInitData.m_colorBufferFormat[0] = m_2DRenderTarget.GetColorBufferFormat();
	//	
	//	m_mainSprite.Init(spriteInitData);
	}

	void RenderingEngine::InitShadowMapRenderTarget()
	{
		
		//カメラの位置これはライトの位置
		m_lightCamera.SetPosition(g_camera3D->GetPosition()+SHADOW_CAMERA_POS);
		
		//カメラの注視点を設定。これがライトを照らしている場所
		m_lightCamera.SetTarget(g_camera3D->GetTarget() + SHADOW_CAMERA_TAR);

		//上方向を設定
		m_lightCamera.SetUp(0, 1, 0);

		//画角を設定する
		m_lightCamera.SetViewAngle(Math::DegToRad(50.0f));
		m_lightCamera.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);
		m_lightCamera.Update();

		//ライトビュープロテクションを行列に計算している
		m_lightCB.shadowCB.mLVP = m_lightCamera.GetViewProjectionMatrix();


		m_lightCamera.Update();

		//シャドウマップ用のレンダリングターゲットを初期化
		float clearColor[4] = { 1.0f,1.0f,1.0f,1.0f };
		m_shadowMapRenderTarget.Create(
			5192,
			5192,
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);


	}



	void RenderingEngine::Execute(RenderContext& rc)
	{
		//シャドウマップの描画。
		RenderShadowMap(rc);

		//フォワードレンダリング
		ModelRendering(rc);

		//ブルームの描画。
		m_bloom.Render(rc, m_mainRenderTarget);

		//2Dスプライトの描画。
		Render2D(rc);

		m_renderObjects.clear();
	}

	//モデルリストに入れられたモデルを描画する
	void RenderingEngine::ModelRendering(RenderContext& rc)
	{
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);
		rc.SetRenderTargetAndViewport(m_mainRenderTarget);
		rc.ClearRenderTargetView(m_mainRenderTarget);

		for (auto& modelobj : m_renderObjects)
		{
			modelobj->OnRenderModel(rc);
		}
		//rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);
	}

	void RenderingEngine::RenderShadowMap(RenderContext& rc)
	{
		// カメラの位置を設定。
		m_lightCamera.SetPosition(Vector3(g_camera3D->GetTarget() + SHADOW_CAMERA_POS));
		m_lightCamera.SetTarget(Vector3(g_camera3D->GetTarget() + SHADOW_CAMERA_TAR));
		m_lightCamera.Update();

		m_lightCB.shadowCB.mLVP = m_lightCamera.GetViewProjectionMatrix();
		m_lightCB.shadowCB.lightPos = m_lightCamera.GetPosition();
		

		//シャドウマップ用のレンダリングターゲットの書き込み待ち
		rc.WaitUntilToPossibleSetRenderTarget(m_shadowMapRenderTarget);
		rc.SetRenderTargetAndViewport(m_shadowMapRenderTarget);
		rc.ClearRenderTargetView(m_shadowMapRenderTarget);

		//描画処理
		for (auto& shadowMaps : m_renderObjects)
		{
			shadowMaps->OnRenderShadowMap(rc,m_lightCamera);
		}

		rc.WaitUntilFinishDrawingToRenderTarget(m_shadowMapRenderTarget);
	}


	void RenderingEngine::Render2D(RenderContext& rc)
	{
		////レンダリングターゲット書き込み待ち。
		//rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);
		//rc.SetRenderTargetAndViewport(m_mainRenderTarget);
		//rc.ClearRenderTargetView(m_mainRenderTarget);

		//描画処理
		for (auto& sprites : m_renderObjects)
		{
			sprites->OnRender2D(rc);
		}
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);

	}
}
