#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {
	RenderingEngine* RenderingEngine::m_instance = nullptr;
	RenderingEngine::RenderingEngine()
	{
		
	}

	RenderingEngine::~RenderingEngine()
	{

	}

	void RenderingEngine::Init()
	{
		//ディレクションライトの設定
		SetDirectionLight(Vector3(1, -1, 1), Vector3(0.5f, 0.5f, 0.5f));

		//環境光の設定
		SetAmbient(1.0f);

		//半球ライトの設定
		SetHemiSphereLight(
			Vector3(1.0f, 0.5f, 0.3f),
			Vector3(0.15f, 0.7f, 0.95f),
			Vector3(0.0f, 1.0f, 0.0f)
		);

		m_lightCB.directionLig = m_directionLig.GetDirectionLig();

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

		//ブルームの設定
		SetBloomThreshold(0.2f);
		m_bloom.Init(m_mainRenderTarget);

		
		//Init2DRenderTarget();

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
	}

	void RenderingEngine::Execute(RenderContext& rc)
	{
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);
		rc.SetRenderTargetAndViewport(m_mainRenderTarget);
		rc.ClearRenderTargetView(m_mainRenderTarget);
		ModelRendering(rc);
		Render2D(rc);
		FontRendering(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);


		m_bloom.Render(rc, m_mainRenderTarget);
		m_spriteList.clear();
		m_modeList.clear();
		m_fontList.clear();
	}

	//モデルリストに入れられたモデルを描画する
	void RenderingEngine::ModelRendering(RenderContext& rc)
	{
		for (auto& modelobj : m_modeList)
		{
			modelobj->OnRenderModel(rc);
		}
	}

	void RenderingEngine::Render2D(RenderContext& rc)
	{
		for (auto& renderObj : m_spriteList)
		{
			renderObj->OnRender2D(rc);
		}
	}

	void RenderingEngine::FontRendering(RenderContext& rc)
	{
		for (auto& fontobj:m_fontList)
		{
			fontobj->OnRender(rc);
		}
	}
}
