#include "k2EngineLowPreCompile.h"
#include "SpriteRender.h"
#include "RenderingEngine.h"
namespace nsK2EngineLow {
	void SpriteRender::Init(
		const char* filePath,
		const float w,
		const float h,
		AlphaBlendMode alphaBlendMode,
		const int clipMode
	)
	{
		SpriteInitData initData;
		//DDSファイルパスのファイルパスを指定する
		initData.m_ddsFilePath[0] = filePath;
		//Sprite表示用のシェーダーのファイルパスを指定する。
		initData.m_fxFilePath = "Assets/shader/sprite.fx";
		//スプライトの幅と高さを指定する
		initData.m_width = static_cast<UINT>(w);
		initData.m_height = static_cast<UINT>(h);
		initData.m_alphaBlendMode = alphaBlendMode;

		ClipMode(initData, clipMode);

		//Sprite初期化オブジェクトを使用して、Spriteを初期化する
		m_sprite.Init(initData);
	}

	void SpriteRender::ClipMode(SpriteInitData& initData, const int clipMode)
	{
		switch (clipMode) {
		case 1:
			initData.m_psEntryPoinFunc = "PSCircleGauge";
			initData.m_expandConstantBuffer = &RenderingEngine::GetInstance()->GetSpriteCB();
			initData.m_expandConstantBufferSize = sizeof(RenderingEngine::GetInstance()->GetSpriteCB());
			break;
		case 2:
			initData.m_psEntryPoinFunc = "PSMainUVScroll";
			initData.m_expandConstantBuffer = &RenderingEngine::GetInstance()->GetSpriteCB();
			initData.m_expandConstantBufferSize = sizeof(RenderingEngine::GetInstance()->GetSpriteCB());
			break;
		}
	}

	void SpriteRender::Draw(RenderContext& rc)
	{
		RenderingEngine::GetInstance()->AddRenderObject(this);
	}
}