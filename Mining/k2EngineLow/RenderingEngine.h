#pragma once

namespace nsK2EngineLow {
	class ModelRender;
	class SpriteRender;
	class RenderTarget;
	class FontRender;
	class DirectionLight;
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
			PointLight::pointLight pointLig[2];
			SpotLight::spotLight spotLig[1];
			HemiSphereLight::hemiSphereLight hemiSphereLig;
			ShadowParamCB shadowCB;
			int ptNum;										//�|�C���g���C�g�̐�
			int spNum;										//�X�|�b�g���C�g�̐�
		
		};

		// �X�v���C�g�p�̍\����
		struct SpriteCB
		{
			float angle;
		};

	//private:
		RenderingEngine();
		~RenderingEngine();

		

	public:

		/// <summary>
		/// �C���X�^���X�̐���
		/// </summary>
		static void CreateInstance()
		{
			m_instance = new RenderingEngine;
			m_instance->Init();
		}
		/// <summary>
		/// �C���X�^���X�̍폜
		/// </summary>
		static void DeleteInstance()
		{
			delete m_instance;
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
		/// �����_�[�I�u�W�F�N�g��ǉ�
		/// </summary>
		/// <param name="renderObject"></param>
		void AddModelRenderObject(ModelRender* renderObject)
		{
			m_modeList.emplace_back(renderObject);
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
		/// �X�v���C�g�p�̍\���̂��擾
		/// </summary>
		/// <returns></returns>
		SpriteCB& GetSpriteCB()
		{
			return m_spiteCB;
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
		/// ���f���̕`��
		/// </summary>
		/// <param name="rc"></param>
		void ModelRendering(RenderContext& rc);

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
		static RenderingEngine*		m_instance;							//���C�g�p�̍\����
		
		DirectionLight				m_directionLig;						//�f�B���N�V���i�����C�g�̍\����
		LightCB						m_lightCB;
		SpriteCB					m_spiteCB;							//�X�v���C�g�p�̍\����
		HemiSphereLight				m_hemiShereLig;
		Bloom						m_bloom;							//�u���[��
		


		RenderTarget				m_mainRenderTarget;					//���C�������_�[�^�[�Q�b�g
		RenderTarget				m_2DRenderTarget;					//2D�����_�[�^�[�Q�b�g
		RenderTarget				m_shadowMapRenderTarget;
		
		Sprite						m_2DSprite;							//2D�X�v���C�g
		Sprite						m_mainSprite;
		Sprite sprite;
		
										
		Camera						m_lightCamera;						//�`��p�̃��C�g�J�������쐬����



		std::vector<SpriteRender*>  m_spriteList;						//�����_�����O����I�u�W�F�N�g
		std::vector<ModelRender*>	m_modeList;							//���f�����X�g
		std::vector<FontRender*>	m_fontList;							//�t�H���g���X�g
		std::vector<IRenderer*>		m_renderObjects;


	};
}


