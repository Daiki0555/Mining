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
	/// モデルの初期化
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	/// <param name="animationClips">アニメーションクリップ</param>
	/// <param name="numAnimationClips">アニメーションの数</param>
	/// <param name="enModelUpAxis">モデルの上軸方向</param>
	void ModelRender::Init(
		const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis
	)
	{
		//スケルトンの初期化
		InitSkeleton(filePath);

		//アニメーションの初期化
		InitAnimation(animationClips, numAnimationClips, enModelUpAxis);
	
		InitModel(filePath, enModelUpAxis);
	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		//スケルトンデータの読み込み
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
		//通常モデルの初期化
		ModelInitData modelInitData;
		modelInitData.m_tkmFilePath = tkmFilePath;
		modelInitData.m_modelUpAxis = modelUpAxis;
		modelInitData.m_fxFilePath = "Assets/shader/model.fx";

		//アニメーションがあるなら
		if (m_skeleton.IsInited()){
			//スケルトンを指定する
			modelInitData.m_skeleton = &m_skeleton;
			modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		}
		m_model.Init(modelInitData);
	}

	void ModelRender::Update()
	{
		//アニメーションが再生されているなら
		if (m_skeleton.IsInited()) {
			m_skeleton.Update(m_model.GetWorldMatrix());
		}
		UpdateWorldMatrixInModes();
		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
	}

	void ModelRender::UpdateWorldMatrixInModes()
	{
		//プレイヤーの座標、回転、大きさを求める
		m_model.UpdateWorldMatrix(m_position, m_rotaition, m_scale);
	}


	void ModelRender::Draw(RenderContext& rc)
	{
		RenderingEngine::GetInstance()->AddRenderObject(this);
	}
}