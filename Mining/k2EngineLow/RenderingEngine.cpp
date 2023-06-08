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
		//���C�������_�[�^�[�Q�b�g��ݒ�
		/*float clearColor[4] = { 0.5f,0.5f,0.5f,1.0f };
		m_mainRenderTarget.Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT,
			clearColor
		);*/
		
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

		//�ŏI�����p�X�v���C�g�̏�����
		SpriteInitData finalSpriteInitData;
		finalSpriteInitData.m_textures[0] = &m_2DRenderTarget.GetRenderTargetTexture();
		// �𑜓x��mainRenderTarget�̕��ƍ���
		finalSpriteInitData.m_width = m_mainRenderTarget.GetWidth();
		finalSpriteInitData.m_height = m_mainRenderTarget.GetHeight();
		// 2D�p�̃V�F�[�_�[���g�p����
		finalSpriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		finalSpriteInitData.m_vsEntryPointFunc = "VSMain";
		finalSpriteInitData.m_psEntryPoinFunc = "PSMain";
		//�㏑��
		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
		//�����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g
		finalSpriteInitData.m_colorBufferFormat[0] = m_mainRenderTarget.GetColorBufferFormat();
		
		m_2DSprite.Init(finalSpriteInitData);

		//2D�����p�X�v���C�g�̏�����
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
		ModelRendering(rc);
		Render2D(rc);
		m_spriteList.clear();
		m_modeList.clear();
	}

	//���f�����X�g�ɓ����ꂽ���f����`�悷��
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
}
