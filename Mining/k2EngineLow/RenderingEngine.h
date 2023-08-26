#pragma once
namespace nsK2EngineLow {
	namespace
	{
		const int POINTLIGHT_NUM = 2;		//�|�C���g���C�g�̐�
		const int SPOTLIGHT_NUM = 1;		//�X�|�b�g���C�g�̐�
	}
	class RenderingEngine:public Noncopyable
	{
	public:

		struct ShadowParamCB
		{
			Vector3 lightPos = Vector3::Zero;
			float pad0=0.0f;
			Matrix mLVP = g_matIdentity;
		};

		//���C�g�̍\����
		struct LightCB
		{
			DirectionLight::directionLight directionLig;
			PointLight::pointLight pointLig[POINTLIGHT_NUM];
			SpotLight::spotLight spotLig[SPOTLIGHT_NUM];
			HemiSphereLight::hemiSphereLight hemiSphereLig;
			ShadowParamCB shadowCB;
			int ptNum;										//�|�C���g���C�g�̐�
			int spNum;										//�X�|�b�g���C�g�̐�
		
		};

		// �X�v���C�g�p�̍\����
		struct SpriteCB
		{
			Vector3 clipSize;								// �N���b�v�T�C�Y
			float fadeValue;								// �t�F�[�h�l
			int clipMode = 0;
		};

		RenderingEngine();
		~RenderingEngine();

		

	public:

		/// <summary>
		/// �C���X�^���X�̐���
		/// </summary>
		static void CreateInstance()
		{
			if (m_instance != nullptr)
			{
				std::abort();
			}
			m_instance = new RenderingEngine;
			m_instance->Init();			
		}
		/// <summary>
		/// �C���X�^���X�̍폜
		/// </summary>
		static void DeleteInstance()
		{
			delete m_instance;
			m_instance = nullptr;
		}
		/// <summary>
		/// �C���X�^���X�̎擾
		/// </summary>
		/// <returns></returns>
		static RenderingEngine* GetInstance()
		{
			if (m_instance == nullptr) {
				CreateInstance();
			}

			return m_instance;
		}
		
		/// <summary>
		/// �����_�[�I�u�W�F�N�g��ǉ�
		/// </summary>
		/// <param name="renderObject"></param>
		void AddRenderObject(IRenderer* renderObject)
		{
			m_renderObjects.emplace_back(renderObject);
		}

		/// <summary>
		/// ���C�g�p�̍\���̂��擾
		/// </summary>
		/// <returns></returns>
		LightCB& GetLightCB()
		{
			return m_lightCB;
		}

		/// <summary>
		/// �V���h�E�p�̍\���̂��擾
		/// </summary>
		/// <returns></returns>
		ShadowParamCB& GetShadowParamCB()
		{
			return m_lightCB.shadowCB;
		}

		/// <summary>
		/// �X�v���C�g�p�̍\���̂��擾
		/// </summary>
		/// <returns></returns>
		SpriteCB& GetSpriteCB()
		{
			return m_spiteCB;
		}

		/// <summary>
		/// �f�B���N�V���i�����C�g�̐ݒ�B
		/// </summary>
		/// <param name="dir">���C�g�̕����B</param>
		/// <param name="color">���C�g�̃J���[�B[</param>
		void SetDirectionLight(const Vector3& dir, const Vector3 color)
		{
			m_directionLig.SetDirection(dir);
			m_directionLig.SetColor(color);
			GetLightCB().directionLig = m_directionLig.GetDirectionLig();
		}

		/// <summary>
		/// �����̐ݒ�
		/// </summary>
		/// <param name="amb">�����̋���</param>
		void SetAmbient(const float amb)
		{
			m_directionLig.SetAmbientLight(amb);
			GetLightCB().directionLig = m_directionLig.GetDirectionLig();
		}

		/// <summary>
		/// �|�C���g���C�g�̐ݒ�
		/// </summary>
		/// <param name="ptNum">�|�C���g���C�g�̐�</param>
		/// <param name="ptlig">�|�C���g���C�g�̍\����</param>
		void SetPointLight(const int ptNum, PointLight::pointLight& ptlig)
		{
			GetLightCB().pointLig[ptNum].ptPosition = ptlig.ptPosition;
			GetLightCB().pointLig[ptNum].ptColor = ptlig.ptColor;
			GetLightCB().pointLig[ptNum].ptRange = ptlig.ptRange;
		}

		/// <summary>
		/// �X�|�b�g���C�g�̐ݒ�
		/// </summary>
		/// <param name="spNum">�X�|�b�g���C�g�̐�</param>
		/// <param name="splig">�X�|�b�g���C�g�̍\����</param>
		void SetSpotLight(const int spNum, SpotLight::spotLight& splig)
		{
			GetLightCB().spotLig[spNum].spPosition = splig.spPosition;
			GetLightCB().spotLig[spNum].spColor = splig.spColor;
			GetLightCB().spotLig[spNum].spRange = splig.spRange;
			GetLightCB().spotLig[spNum].spDirection = splig.spDirection;
			GetLightCB().spotLig[spNum].spAngle = splig.spAngle;
		}

		/// <summary>
		/// �������C�g��ݒ�B
		/// </summary>
		void SetHemiSphereLight(const Vector3& grdColor, const Vector3& skyColor, const Vector3& grdNormal)
		{
			m_hemiShereLig.SetGroundColor(grdColor);
			m_hemiShereLig.SetSkyColor(skyColor);
			m_hemiShereLig.SetGroundNormal(grdNormal);
			GetLightCB().hemiSphereLig = m_hemiShereLig.GetHemiSphereLig();
		}

		/// <summary>
		/// �u���[����臒l��ݒ�
		/// </summary>
		/// <param name="threshold">臒l</param>
		void SetBloomThreshold(const float threshold)
		{
			m_bloom.SetThreshold(threshold);
		}

		/// <summary>
		/// �V���h�E�}�b�v�̃����_�����O�^�[�Q�b�g���擾
		/// </summary>
		/// <returns></returns>
		RenderTarget& GetShadowMapRenderTarget()
		{
			return m_shadowMapRenderTarget;
		}


		/// <summary>
		/// ����������
		/// </summary>
		void Init();

		/// <summary>
		/// ���s����
		/// </summary>
		/// <param name="rc"></param>
		void Execute(RenderContext& rc);
	private:
		/// <summary>
		/// ���C�g�̏�����
		/// </summary>
		void InitLight();

		/// <summary>
		/// ���C�������_�����O�^�[�Q�b�g��������
		/// </summary>
		void InitMainRenderTarget();

		/// <summary>
		/// �V���h�E�}�b�v�p�̃����_�[�^�[�Q�b�g���������B
		/// </summary>
		void InitShadowMapRenderTarget();

		/// <summary>
		/// 2D�����_�[�^�[�Q�b�g��������
		/// </summary>
		void Init2DRenderTarget();

		/// <summary>
		///G-Buffer�̏�����
		/// </summary>
		void InitGBffer();


		/// <summary>
		/// �f�B�t�@�[�h���C�e�B���O
		/// </summary>
		/// <param name="rc"></param>
		void DefferedRender(RenderContext& rc);

		/// <summary>
		/// �V���h�E�}�b�v�̕`�揈��
		/// </summary>
		/// <param name="rc"></param>
		void RenderShadowMap(RenderContext& rc);

		/// <summary>
		/// 2D�`�揈��
		/// </summary>
		/// <param name="rc"></param>
		void Render2D(RenderContext& rc);

	private:
		//GBuffer�̒�`
		enum EnGBffer
		{
			enGBuffer_Albedo,			//�A���x�h
			enGBuffer_Normal,			//�@��
			enGBuffer_WorldPos,			//���[���h���W
			enGBuffer_MetalSmooth,		//�����x�Ɗ��炩���Bx�ɋ����x�Aw�Ɋ��炩�����L�^����Ă���B
			enGBuffer_ShadowParam,		//�e�̃p�����[�^
			enGBuffer_Num,				//GBuffer�̐�
		};

		static RenderingEngine*		m_instance;							//���C�g�p�̍\����
		
		DirectionLight				m_directionLig;						//�f�B���N�V���i�����C�g�̍\����
		LightCB						m_lightCB;
		SpriteCB					m_spiteCB;							//�X�v���C�g�p�̍\����
		HemiSphereLight				m_hemiShereLig;
		Bloom						m_bloom;							//�u���[��
		


		RenderTarget				m_mainRenderTarget;					//���C�������_�[�^�[�Q�b�g
		RenderTarget				m_2DRenderTarget;					//2D�����_�[�^�[�Q�b�g
		RenderTarget				m_shadowMapRenderTarget;
		RenderTarget			    m_gBuffer[enGBuffer_Num];			//G-Buffer
		
		Sprite						m_2DSprite;							//2D�X�v���C�g
		Sprite						m_mainSprite;
		Sprite						m_defferedLightInSpr;				//�f�B�t�@�[�h���C�e�B���O�p�̃X�v���C�g

		SpriteInitData				m_deferredSpriteInitData;			//�f�B�t�@�[�h���C�e�B���O���s�����߂̃X�v���C�g�̏�����
		
										
		Camera						m_lightCamera;						//�`��p�̃��C�g�J�������쐬����



		std::vector<IRenderer*>		m_renderObjects;					//


	};
}


