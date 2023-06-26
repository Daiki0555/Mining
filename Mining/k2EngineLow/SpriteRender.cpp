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
		//DDS�t�@�C���p�X�̃t�@�C���p�X���w�肷��
		initData.m_ddsFilePath[0] = filePath;
		//Sprite�\���p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
		initData.m_fxFilePath = "Assets/shader/sprite.fx";
		//�X�v���C�g�̕��ƍ������w�肷��
		initData.m_width = static_cast<UINT>(w);
		initData.m_height = static_cast<UINT>(h);
		initData.m_alphaBlendMode = alphaBlendMode;

		ClipMode(initData, clipMode);

		//Sprite�������I�u�W�F�N�g���g�p���āASprite������������
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
		}
	}

	void SpriteRender::Draw(RenderContext& rc)
	{
		RenderingEngine::GetInstance()->AddRenderObject(this);
	}
}