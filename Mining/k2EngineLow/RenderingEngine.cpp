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
		SetAmbient(0.7f);

		//�������C�g�̐ݒ�
		/*SetHemiSphereLight(
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

		
	}

	void RenderingEngine::InitShadowMapRenderTarget()
	{
		//�J�����̈ʒu����̓��C�g�̈ʒu
		m_lightCamera.SetPosition(g_camera3D->GetTarget() + Vector3(0,600,0));

		//�J�����̒����_��ݒ�B���ꂪ���C�g��Ƃ炵�Ă���ꏊ
		m_lightCamera.SetTarget(g_camera3D->GetTarget());

		//�������ݒ�
		m_lightCamera.SetUp(0, 1, 0);

		m_lightCamera.SetFar(5000.0f);

		//��p��ݒ肷��
		//m_lightCamera.SetViewAngle(Math::DegToRad(20.0f));
		//m_lightCamera.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);
		m_lightCamera.Update();

		//���C�g�r���[�v���e�N�V������s��Ɍv�Z���Ă���
		m_lightCB.shadowCB.mLVP = m_lightCamera.GetViewProjectionMatrix();	

		//�V���h�E�}�b�v�p�̃����_�����O�^�[�Q�b�g�������
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
		//�A���x�h�J���[�p�̃����_�[�^�[�Q�b�g
		float clearColor[4] = { 0.5f,0.5f,0.5f,1.0f };
		m_gBuffer[enGBuffer_Albedo].Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);
		//�@���������ݗp�̃����_�[�^�[�Q�b�g
		m_gBuffer[enGBuffer_Normal].Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1, 1,
			DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_UNKNOWN
		);
		//�s�N�Z���̃��[���h���W��L�^���邽�߂�G-Buffer��쐬
		m_gBuffer[enGBuffer_WorldPos].Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1, 1,
			DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_UNKNOWN
		);

		//����x�Ɗ��炩���}�b�v�o�͗p�̃����_�[�^�[�Q�b�g�������
		m_gBuffer[enGBuffer_MetalSmooth].Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM, //�������g�p�ʃ������������ݑ��x�D��ŁA8bit�̕����Ȃ������o�b�t�@��g�p����B�B
			DXGI_FORMAT_UNKNOWN
		);

		//�e�̃p�����[�^��o�͗p�̃����_�����O�^�[�Q�b�g�������
		m_gBuffer[enGBuffer_ShadowParam].Create(
			g_graphicsEngine->GetFrameBufferWidth(),
			g_graphicsEngine->GetFrameBufferHeight(),
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT
		);

		//�f�B�t�@�[�h���C�e�B���O��s�����߂̃X�v���C�g�����������
		//��ʑS�̂Ƀ����_�����O����̂ŕ��ƍ����̓t���[���o�b�t�@�[�̕��ƍ����Ɠ���
		m_deferredSpriteInitData.m_width = FRAME_BUFFER_W;
		m_deferredSpriteInitData.m_height = FRAME_BUFFER_H;

		//�g�p����e�N�X�`���̓A���x�h�e�N�X�`���Ɩ@���e�N�X�`��
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

		//�������f�[�^��g���ăX�v���C�g��쐬
		m_defferedLightInSpr.Init(m_deferredSpriteInitData);
	}

	void RenderingEngine::Execute(RenderContext& rc)
	{
		//�V���h�E�}�b�v�̕`��B
		RenderShadowMap(rc);	

		//�f�B�t�@�[�h�����_�����O
		DefferedRender(rc);

		//�u���[���̕`��B
		m_bloom.Render(rc, m_mainRenderTarget);

		//2D�X�v���C�g�̕`��B
		Render2D(rc);

	

		m_renderObjects.clear();
	}

	//���f�����X�g�ɓ����ꂽ���f����`�悷��
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

		//�����_�����O���t���[���o�b�t�@�[�ɖ߂��ăX�v���C�g������_�����O����
		g_graphicsEngine->ChangeRenderTargetToFrameBuffer(rc);

		//G-Buffer�̓�e���ƂɃX�v���C�g������_�����O����
		//m_defferedLightInSpr.Draw(rc);
	}

	void RenderingEngine::RenderShadowMap(RenderContext& rc)
	{

		//�J�����̈ʒu����̓��C�g�̈ʒu
		m_lightCamera.SetPosition(g_camera3D->GetTarget() + Vector3(200,600,300) * 1.0f);
		//�J�����̒����_��ݒ�B���ꂪ���C�g��Ƃ炵�Ă���ꏊ
		m_lightCamera.SetTarget(g_camera3D->GetTarget());
		m_lightCamera.Update();
		

		m_lightCB.shadowCB.mLVP = m_lightCamera.GetViewProjectionMatrix();
		m_lightCB.shadowCB.lightPos = m_lightCamera.GetPosition();
		

		//�V���h�E�}�b�v�p�̃����_�����O�^�[�Q�b�g�̏������ݑ҂�
		rc.WaitUntilToPossibleSetRenderTarget(m_shadowMapRenderTarget);
		rc.SetRenderTargetAndViewport(m_shadowMapRenderTarget);
		rc.ClearRenderTargetView(m_shadowMapRenderTarget);

		//�`�揈��
		for (auto& shadowMaps : m_renderObjects){
			shadowMaps->OnRenderShadowMap(rc,m_lightCamera);
		}

		rc.WaitUntilFinishDrawingToRenderTarget(m_shadowMapRenderTarget);
	}


	void RenderingEngine::Render2D(RenderContext& rc)
	{
		////�����_�����O�^�[�Q�b�g�������ݑ҂��B
		rc.WaitUntilToPossibleSetRenderTarget(m_mainRenderTarget);
		rc.SetRenderTargetAndViewport(m_mainRenderTarget);
		rc.ClearRenderTargetView(m_mainRenderTarget);
		
		m_defferedLightInSpr.Draw(rc);
		
		//�`�揈��
		for (auto& sprites : m_renderObjects){
			sprites->OnRender2D(rc);
		}
		
		rc.WaitUntilFinishDrawingToRenderTarget(m_mainRenderTarget);

	}
}
