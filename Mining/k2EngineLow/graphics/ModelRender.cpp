#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow {

	ModelRender::ModelRender()
	{

	}

	ModelRender::~ModelRender()
	{

	}
	/// <summary>
	/// ���f���̏�����
	/// </summary>
	/// <param name="filePath">�t�@�C���p�X</param>
	/// <param name="animationClips">�A�j���[�V�����N���b�v</param>
	/// <param name="numAnimationClips">�A�j���[�V�����̐�</param>
	/// <param name="enModelUpAxis">���f���̏㎲����</param>
	void ModelRender::Init(
		const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis
	)
	{
		//�X�P���g���̏�����
		InitSkeleton(filePath);

		//�A�j���[�V�����̏�����
		InitAnimation(animationClips, numAnimationClips, enModelUpAxis);
	
		InitModel(filePath, enModelUpAxis);
	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		//�X�P���g���f�[�^�̓ǂݍ���
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr)
		{
			m_animation.Init(
				m_skeleton,
				m_animationClips,
				numAnimationClips
			);
		}
	}

	void ModelRender::InitModel(const char* tkmFilePath, EnModelUpAxis modelUpAxis)
	{
		//�ʏ탂�f���̏�����
		ModelInitData modelInitData;
		modelInitData.m_tkmFilePath = tkmFilePath;
		modelInitData.m_modelUpAxis = modelUpAxis;
		modelInitData.m_fxFilePath = "Assets/shader/model.fx";

		//�A�j���[�V����������Ȃ�
		if (m_skeleton.IsInited()){
			//�X�P���g�����w�肷��
			modelInitData.m_skeleton = &m_skeleton;
			modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		}
		m_model.Init(modelInitData);
	}

	void ModelRender::Update()
	{
		//�A�j���[�V�������Đ�����Ă���Ȃ�
		if (m_skeleton.IsInited()) {
			m_skeleton.Update(m_model.GetWorldMatrix());
		}
		UpdateWorldMatrixInModes();
		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
	}

	void ModelRender::UpdateWorldMatrixInModes()
	{
		//�v���C���[�̍��W�A��]�A�傫�������߂�
		m_model.UpdateWorldMatrix(m_position, m_rotaition, m_scale);
	}


	void ModelRender::Draw(RenderContext& rc)
	{
		RenderingEngine::GetInstance()->AddRenderObject(this);
	}
}