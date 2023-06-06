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

	//モデルリストに入れられたモデルを描画する
	void RenderingEngine::ModelRendering(RenderContext& rc)
	{
		for (auto& modelobj : m_modelList)
		{
			modelobj->OnRenderModel(rc);
		}
	}

	void RenderingEngine::Execute(RenderContext& rc)
	{
		ModelRendering(rc);
		m_modelList.clear();
	}
}
