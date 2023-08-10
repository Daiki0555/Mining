#pragma once

namespace nsK2EngineLow {
	
	class ModelRender : public IRenderer
	{
	public:
		ModelRender();
		~ModelRender();
		
		/// <summary>
		/// ����������
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X</param>
		/// <param name="animationClip">�A�j���[�V�����N���b�v</param>
		/// <param name="numAnimationClips">�A�j���[�V�����̐�</param>
		/// <param name="enModelUpAxis">���f���̏����</param>
		/// <param name="isShadow">true�Ȃ�e��^����</param>
		/// <param name="isShadowReceiver">true�Ȃ�e�𗎂Ƃ�</param>
		void Init(
			const char* filePath,
			AnimationClip* animationClip = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
			const bool isShadow = false,
			const bool isShadowReceiver = false
		);

		/// <summary>
		/// ����ȃV�F�[�f�B���O���s�������ꍇ�̏���������
		/// </summary>
		/// <param name="initData"></param>
		//void InitForwarRendering(ModelInitData& initData);

		/// <summary>
		/// �X�V����
		/// </summary>
		void Update();
		/// <summary>
		/// �`�揈��
		/// </summary>
		/// <param name="rc"></param>
		void Draw(RenderContext& rc);
		/// <summary>
		/// �A�j���[�V�����̍Đ�
		/// </summary>
		/// <param name="animNo">�A�j���[�V�����N���b�v�̔ԍ�</param>
		/// <param name="interpolateTime">�⊮����(�P�ʁF�b)</param>
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}
		/// <summary>
		/// �A�j���[�V�������Đ������ǂ���
		/// </summary>
		/// <returns></returns>
		bool IsPlayingAnimation()const
		{
			return m_animation.IsPlaying();
		}
		/// <summary>
		/// ���f���̎擾
		/// </summary>
		/// <returns></returns>
		Model& GetModel()
		{
			return m_model;
		}
		/// <summary>
		/// ���W�̐ݒ�
		/// </summary>
		/// <param name="pos">���W</param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// ���W�̎擾
		/// </summary>
		/// <returns></returns>
		const Vector3 GetPosition()
		{
			return m_position;
		}
		/// <summary>
		/// ��]�̐ݒ�
		/// </summary>
		/// <param name="rotaition">��]</param>
		void SetRotaition(const Quaternion& rotaition)
		{
			m_rotaition = rotaition;
		}
		/// <summary>
		/// �g�嗦�̐ݒ�
		/// </summary>
		/// <param name="scale">�g�嗦</param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}

		/// <summary>
		/// �A�j���[�V�����Đ��̑��x��ݒ肷��
		/// </summary>
		/// <param name="animationSpeed">���l�̕������{�ɂ���@</param>
		void SetAnimationSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}

		/// <summary>
		/// �{�[�����O����{�[���ԍ�������
		/// </summary>
		/// <param name="boneName">�{�[���̖��O</param>
		/// <returns></returns>
		int FindBoneID(const wchar_t* boneName) const
		{
			return m_skeleton.FindBoneID(boneName);
		}
		/// <summary>
		/// �{�[���ԍ�����{�[�����擾
		/// </summary>
		/// <param name="boneNo">�{�[���ԍ�</param>
		/// <returns></returns>
		Bone* GetBone(int boneNo)const
		{
			return m_skeleton.GetBone(boneNo);
		}

	public:
		/// <summary>
		/// ���f����`�悷��(RenderingEngine�ŕ`�悷��Ƃ��ɌĂяo��)
		/// </summary>
		/// <param name="rc"></param>
		void OnRenderModel(RenderContext& rc)override
		{
			if (m_model.IsInited())
			{
				m_model.Draw(rc);
			}
		}

		/// <summary>
		/// �e�̂��郂�f����`�悷��
		/// </summary>
		/// <param name="rc"></param>
		void OnRenderShadowMap(RenderContext& rc, Camera& camera)override
		{
			if (m_shadowModels.IsInited())
			{
				m_shadowModels.Draw(rc, camera);
			}
		}

	private:
		/// <summary>
		/// �X�P���g���̏�����
		/// </summary>
		/// <param name="filePath"></param>
		void InitSkeleton(const char* filePath);

		/// <summary>
		/// �A�j���[�V�����̏�����
		/// </summary>
		/// <param name="animationClips">�A�j���[�V�����N���b�v</param>
		/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐�</param>
		/// <param name="enModelUpAxis">���f���̏����</param>
		void InitAnimation(AnimationClip* animationClips,
			int numAnimationClips,
			EnModelUpAxis enModelUpAxis);

		/// <summary>
		/// ���f���̏�����
		/// </summary>
		/// <param name="tkmFilePath">�t�@�C���p�X</param>
		/// <param name="modelUpAxis">���f���̏����</param>
		///<param name = "isShadow">true�Ȃ�e��^����< / param>
		/// <param name=isShadowReceiver">true�Ȃ�e�𗎂Ƃ�</param>
		void InitModel(
			const char* tkmFilePath,
			EnModelUpAxis modelUpAxis,
			const bool isShadow,
			const bool isShadowReceiver
		);

		/// <summary>
		/// �V���h�E�p�̃��f���̏�����
		/// </summary>
		/// <param name="tkmFilePath">�t�@�C���p�X</param>
		/// <param name="modelUpAxis">���f���̏����</param>
		void InitShadowModel(
			const char* tkmFilePath,
			EnModelUpAxis modelUpAxis
		);


		/// <summary>
		/// �e�탂�f���̃��[���h�s����X�V����B
		/// </summary>
		void UpdateWorldMatrixInModes();

	private:
		AnimationClip*	m_animationClips = nullptr;
		Animation		m_animation;
		int				m_numAnimationClips = 0;					//�A�j���[�V�����N���b�v�̐�
		float			m_animationSpeed = 1.0f;
		bool			m_isUpdateAnimation = true;

		Vector3			m_position = Vector3::Zero;
		Vector3			m_scale = Vector3::One;
		
		Quaternion		m_rotaition = Quaternion::Identity;
		
		EnModelUpAxis	m_enFbxUpAxis = enModelUpAxisZ;
		
		
		Model			m_model;
		Model			m_shadowModels[ NUM_SHADOW_MAP];
		
		Skeleton		m_skeleton;
			
		RenderingEngine m_renderinEngine;
	};
}


