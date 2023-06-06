#pragma once

namespace nsK2EngineLow {
	class RenderingEngine;
	class ModelRender
	{
	public:
		ModelRender();
		~ModelRender();
		/// <summary>
		/// モデルの初期化
		/// </summary>
		/// <param name="filePath"></param>
		void Init(
			const char* filePath,
			AnimationClip* animationClip = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis=enModelUpAxisZ
		);

		/// <summary>
		/// 特殊なシェーディングを行いたい場合の初期化処理
		/// </summary>
		/// <param name="initData"></param>
		//void InitForwarRendering(ModelInitData& initData);

		/// <summary>
		/// 更新処理
		/// </summary>
		void Update();
		/// <summary>
		/// 描画処理
		/// </summary>
		/// <param name="rc"></param>
		void Draw(RenderContext& rc);
		/// <summary>
		/// アニメーションの再生
		/// </summary>
		/// <param name="animNo">アニメーションクリップの番号</param>
		/// <param name="interpolateTime">補完時間(単位：秒)</param>
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}
		/// <summary>
		/// アニメーションが再生中かどうか
		/// </summary>
		/// <returns></returns>
		bool IsPlayingAnimation()const
		{
			return m_animation.IsPlaying();
		}
		/// <summary>
		/// モデルの取得
		/// </summary>
		/// <returns></returns>
		Model& GetModel()
		{
			return m_model;
		}
		/// <summary>
		/// 座標の設定
		/// </summary>
		/// <param name="pos">座標</param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// 座標の取得
		/// </summary>
		/// <returns></returns>
		const Vector3 GetPosition()
		{
			return m_position;
		}
		/// <summary>
		/// 回転の設定
		/// </summary>
		/// <param name="rotaition">回転</param>
		void SetRotaition(const Quaternion& rotaition)
		{
			m_rotaition = rotaition;
		}
		/// <summary>
		/// 拡大率の設定
		/// </summary>
		/// <param name="scale">拡大率</param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// アニメーション再生の速度を設定する
		/// </summary>
		/// <param name="animationSpeed">数値の分だけ倍にする　</param>
		void SetAnimationSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}

		/// <summary>
		/// ボーン名前からボーン番号を検索
		/// </summary>
		/// <param name="boneName">ボーンの名前</param>
		/// <returns></returns>
		int FindBoneID(const wchar_t* boneName) const
		{
			return m_skeleton.FindBoneID(boneName);
		}
		/// <summary>
		/// ボーン番号からボーンを取得
		/// </summary>
		/// <param name="boneNo">ボーン番号</param>
		/// <returns></returns>
		Bone* GetBone(int boneNo)const
		{
			return m_skeleton.GetBone(boneNo);
		}

	public:
		/// <summary>
		/// モデルを描画する(RenderingEngineで描画するときに呼び出す)
		/// </summary>
		/// <param name="rc"></param>
		void OnRenderModel(RenderContext& rc)
		{
			m_model.Draw(rc);
		}

	private:
		/// <summary>
		/// スケルトンの初期化
		/// </summary>
		/// <param name="filePath"></param>
		void InitSkeleton(const char* filePath);

		/// <summary>
		/// アニメーションの初期化
		/// </summary>
		/// <param name="animationClips">アニメーションクリップ</param>
		/// <param name="numAnimationClips">アニメーションクリップの数</param>
		/// <param name="enModelUpAxis">モデルの上向き</param>
		void InitAnimation(AnimationClip* animationClips,
			int numAnimationClips,
			EnModelUpAxis enModelUpAxis);

		/// <summary>
		/// モデルの初期化
		/// </summary>
		/// <param name="tkmFilePath">ファイルパス</param>
		/// <param name="modelUpAxis">モデルの上方向</param>
		void InitModel(
			const char* tkmFilePath,
			EnModelUpAxis modelUpAxis
		);
		/// <summary>
		/// 各種モデルのワールド行列を更新する。
		/// </summary>
		void UpdateWorldMatrixInModes();

	private:
		AnimationClip*	m_animationClips = nullptr;
		int				m_numAnimationClips = 0;					//アニメーションクリップの数

		Vector3			m_position = Vector3::Zero;
		Quaternion		m_rotaition = Quaternion::Identity;
		Vector3			m_scale = Vector3::One;
		EnModelUpAxis	m_enFbxUpAxis = enModelUpAxisZ;
		Animation		m_animation;
		Model			m_model;
		bool			m_isUpdateAnimation = true;
		Skeleton		m_skeleton;
		float			m_animationSpeed=1.0f;

		
	};
}


