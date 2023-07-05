#include "k2EngineLowPreCompile.h"
#include "Bloom.h"
namespace nsK2EngineLow{
	Bloom::Bloom()
	{

	}

	Bloom::~Bloom()
	{

	}

	void Bloom::Init(RenderTarget& mainRenderTarget)
	{
		m_luminanceRenderTarget.Create(
			mainRenderTarget.GetWidth(),
			mainRenderTarget.GetHeight(),
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		//�P�x���o�p�̃X�v���C�g������������
		SpriteInitData spriteInitData;
		//�P�x���o�p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��
		spriteInitData.m_fxFilePath = "Assets/shader/postEffect.fx";

		//���_�V�F�[�_�̃G���g���[�|�C���g���w�肷��
		spriteInitData.m_vsEntryPointFunc = "VSMain";

		//�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
		spriteInitData.m_psEntryPoinFunc = "PSLuminance";

		//�u���[���̏����V�F�[�_�ɓn��
		spriteInitData.m_expandConstantBuffer = &m_luminanceCB;
		spriteInitData.m_expandConstantBufferSize = sizeof(m_luminanceCB);

		//�X�v���C�g�̕��ƍ�����luminaceRenderTarget�Ɠ���
		spriteInitData.m_width = mainRenderTarget.GetWidth();
		spriteInitData.m_height = mainRenderTarget.GetHeight();

		//�e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@�[
		spriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();

		//�������ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��
		spriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		m_luminanceSprite.Init(spriteInitData);

		//�K�E�V�A���u���[��������
		//m_gussianBlur[0]�͋P�x�e�N�X�`���ɃK�E�V�A���u���[���|����
		m_gaussianBlur[0].Init(&m_luminanceRenderTarget.GetRenderTargetTexture());

		//m_gussianBlur[1]��m_gussianBlur[0]�̃e�N�X�`���ɃK�E�V�A���u���[�����|����
		m_gaussianBlur[1].Init(&m_gaussianBlur[0].GetBokeTexture());

		//m_gussianBlur[2]��m_gussianBlur[1]�̃e�N�X�`���ɃK�E�V�A���u���[�����|����
		m_gaussianBlur[2].Init(&m_gaussianBlur[1].GetBokeTexture());

		//m_gussianBlur[3]��m_gussianBlur[2]�̃e�N�X�`���ɃK�E�V�A���u���[�����|����
		m_gaussianBlur[3].Init(&m_gaussianBlur[2].GetBokeTexture());

		//�{�P�摜�����Z��������X�v���C�g��������
		//����������ݒ肷��
		SpriteInitData finalSpriteInitData;
		finalSpriteInitData.m_textures[0] = &m_gaussianBlur[0].GetBokeTexture();
		finalSpriteInitData.m_textures[1] = &m_gaussianBlur[1].GetBokeTexture();
		finalSpriteInitData.m_textures[2] = &m_gaussianBlur[2].GetBokeTexture();
		finalSpriteInitData.m_textures[3] = &m_gaussianBlur[3].GetBokeTexture();

		//�𑜓x��mainRenderTarget�̕��ƍ���
		finalSpriteInitData.m_width = mainRenderTarget.GetWidth();
		finalSpriteInitData.m_height = mainRenderTarget.GetHeight();

		//�ڂ������摜���A�ʏ��2D�Ƃ��ă��C�������_�����O�^�[�Q�b�g�ɕ`�悷��̂ŁA
		//2D�p�̃V�F�[�_�[���g�p����
		finalSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
		finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";

		//���Z�����ŕ`�悷��̂ŁA�A���t�@�u�����f�B���O���[�h�ɉ��Z����
		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;

		//�J���[�o�b�t�@�[�̃t�H�[�}�b�g��32�r�b�g���������_�o�b�t�@�[
		finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32_FLOAT;

		//�������������Ƃɉ��Z�����p�̃X�v���C�g������������
		m_finalSprite.Init(finalSpriteInitData);

		//�e�N�X�`����\��t���邽�߂̃X�v���C�g������������
		SpriteInitData initData;
		//�e�N�X�`����mainRenderTarget�̃J���[�o�b�t�@�[
		initData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
		initData.m_width = mainRenderTarget.GetWidth();
		initData.m_height = mainRenderTarget.GetHeight();
		//���m�N���p�̃V�F�[�_�[���w�肷��
		initData.m_fxFilePath = "Assets/shader/sprite.fx";
		m_copyMainRtSprite.Init(initData);

	}

	void Bloom::Render(RenderContext& rc, RenderTarget& mainRenderTarget)
	{
		//g_graphicsEngine->BeginGPUEvent("Bloom");

		//�P�x���o
		//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX
		rc.WaitUntilToPossibleSetRenderTarget(m_luminanceRenderTarget);

		//�����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTargetAndViewport(m_luminanceRenderTarget);

		//�����_�����O�^�[�Q�b�g���N���A
		rc.ClearRenderTargetView(m_luminanceRenderTarget);

		//�P�x���o���s��
		m_luminanceSprite.Draw(rc);

		//�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		rc.WaitUntilFinishDrawingToRenderTarget(m_luminanceRenderTarget);

		//�K�E�V�A���u���[�����s����
		m_gaussianBlur[0].ExecuteOnGPU(rc, 10);
		m_gaussianBlur[1].ExecuteOnGPU(rc, 10);
		m_gaussianBlur[2].ExecuteOnGPU(rc, 10);
		m_gaussianBlur[3].ExecuteOnGPU(rc, 10);

		//�{�P�摜�����C�������_�����O�^�[�Q�b�g�ɉ��Z����
		//�����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);

		//�����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTargetAndViewport(mainRenderTarget);

		//�ŏI����
		m_finalSprite.Draw(rc);

		//�����_�����O�^�[�Q�b�g�ւ̏������ݑ҂�
		rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

		//���C�������_�����O�^�[�Q�b�g�̊G���t���[���o�b�t�@�[�ɃR�s�[
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);

		// �|�X�g�G�t�F�N�g�̌��ʂ����C�������_�����O�^�[�Q�b�g�ɔ��f�B
		m_copyMainRtSprite.Draw(rc);

		//g_graphicsEngine->EndGPUEvent();



	}
}