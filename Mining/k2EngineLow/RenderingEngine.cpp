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
		//���C�������_�[�^�[�Q�b�g��ݒ�
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
		//�f�B���N�V�������C�g�̐ݒ�
		SetDirectionLight(Vector3(1, -1, 1), Vector3(0.5f, 0.5f, 0.5f));

		//�����̐ݒ�
		SetAmbient(1.0f);

		//�������C�g�̐ݒ�
	/*	SetHemiSphereLight(
			Vector3(1.0f, 0.5f, 0.3f),
			Vector3(0.15f, 0.7f, 0.95f),
			Vector3(0.0f, 1.0f, 0.0f)
		);*/
		//�f�B���N�V���i�����C�g�̎擾
		m_lightCB.directionLig = m_directionLig.GetDirectionLig();

		//�u���[���̐ݒ�
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

		//�~�`�Q�[�W�p�Ɉ�U�R�����g�A�E�g
		//�ŏI�����p�X�v���C�g�̏�����
		SpriteInitData finalSpriteInitData;
		finalSpriteInitData.m_textures[0] = &m_2DRenderTarget.GetRenderTargetTexture();
		// �𑜓x��mainRenderTarget�̕��ƍ���
		finalSpriteInitData.m_width = m_mainRenderTarget.GetWidth();
		finalSpriteInitData.m_height = m_mainRenderTarget.GetHeight();
		// 2D�p�̃V�F�[�_�[��g�p����
		finalSpriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		finalSpriteInitData.m_vsEntryPointFunc = "VSMain";
		finalSpriteInitData.m_psEntryPoinFunc = "PSMain";
		// �~�`�Q�[�W�p�̍\���̂̏���n��
		finalSpriteInitData.m_expandConstantBuffer = &RenderingEngine::GetInstance()->GetSpriteCB();
		finalSpriteInitData.m_expandConstantBufferSize = sizeof(RenderingEngine::GetInstance()->GetSpriteCB());
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

		////�ŏI�����p�X�v���C�g�̏�����
		//SpriteInitData finalSpriteInitData;
		//finalSpriteInitData.m_textures[0] = &m_2DRenderTarget.GetRenderTargetTexture();
		//// �𑜓x��mainRenderTarget�̕��ƍ���
		//finalSpriteInitData.m_width = m_mainRenderTarget.GetWidth();
		//finalSpriteInitData.m_height = m_mainRenderTarget.GetHeight();
		//// 2D�p�̃V�F�[�_�[��g�p����
		//finalSpriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		//finalSpriteInitData.m_vsEntryPointFunc = "VSMain";
		//finalSpriteInitData.m_psEntryPoinFunc = "PSMain";
		////�㏑��
		//finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_None;
		////�����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g
		//finalSpriteInitData.m_colorBufferFormat[0] = m_mainRenderTarget.GetColorBufferFormat();
		//
		//m_2DSprite.Init(finalSpriteInitData);

	//	//2D�����p�X�v���C�g�̏�����
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
		
		//�J�����̈ʒu����̓��C�g�̈ʒu
		m_lightCamera.SetPosition(g_camera3D->GetPosition()+SHADOW_CAMERA_POS);
		
		//�J�����̒����_��ݒ�B���ꂪ���C�g��Ƃ炵�Ă���ꏊ
		m_lightCamera.SetTarget(g_camera3D->GetTarget() + SHADOW_CAMERA_TAR);

		//�������ݒ�
		m_lightCamera.SetUp(0, 1, 0);

		//��p��ݒ肷��
		m_lightCamera.SetViewAngle(Math::DegToRad(50.0f));
		m_lightCamera.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);
		m_lightCamera.Update();

		//���C�g�r���[�v���e�N�V������s��Ɍv�Z���Ă���
		m_lightCB.shadowCB.mLVP = m_lightCamera.GetViewProjectionMatrix();


		m_lightCamera.Update();

		//�V���h�E�}�b�v�p�̃����_�����O�^�[�Q�b�g�������
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
		//�V���h�E�}�b�v�̕`��B
		RenderShadowMap(rc);

		//�t�H���[�h�����_�����O
		ModelRendering(rc);

		//�u���[���̕`��B
		m_bloom.Render(rc, m_mainRenderTarget);

		//2D�X�v���C�g�̕`��B
		Render2D(rc);

		m_renderObjects.clear();
	}

	//���f�����X�g�ɓ����ꂽ���f����`�悷��
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
		// �J�����̈ʒu��ݒ�B
		m_lightCamera.SetPosition(Vector3(g_camera3D->GetTarget() + SHADOW_CAMERA_POS));
		m_lightCamera.SetTarget(Vector3(g_camera3D->GetTarget() + SHADOW_CAMERA_TAR));
		m_lightCamera.Update();

		m_lightCB.shadowCB.mLVP = m_lightCamera.GetViewProjectionMatrix();
		m_lightCB.shadowCB.lightPos = m_lightCamera.GetPosition();
		

		//�V���h�E�}�b�v�p�̃����_�����O�^�[�Q�b�g�̏������ݑ҂�
		rc.WaitUntilToPossibleSetRenderTarget(m_shadowMapRenderTarget);
		rc.SetRenderTargetAndViewport(m_shadowMapRenderTarget);
		rc.ClearRenderTargetView(m_shadowMapRenderTarget);

		//�`�揈��
		for (auto& shadowMaps : m_renderObjects)
		{
			shadowMaps->OnRenderShadowMap(rc,m_lightCamera);
		}

		rc.WaitUntilFinishDrawingToRenderTarget(m_shadowMapRenderTarget);
	}


	void RenderingEngine::Render2D(RenderContext& rc)
	{
		////�����_�����O�^�[�Q�b�g�������ݑ҂��B
		//rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);
		//rc.SetRenderTargetAndViewport(m_mainRenderTarget);
		//rc.ClearRenderTargetView(m_mainRenderTarget);

		//�`�揈��
		for (auto& sprites : m_renderObjects)
		{
			sprites->OnRender2D(rc);
		}
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);

	}
}
