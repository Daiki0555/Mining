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
		struct LightCB
		{
			DirectionLight::directionLight directionLig;
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
		/// <param name="modelRender"></param>
		void AddSpriteRenderObject(SpriteRender* renderObject)
		{
			m_spriteList.emplace_back(renderObject);
		}

		/// <summary>
		/// �����_�[�I�u�W�F�N�g��ǉ�
		/// </summary>
		/// <param name="modelRender"></param>
		void AddModelRenderObject(ModelRender* renderObject)
		{
			m_modeList.emplace_back(renderObject);
		}
		/// <summary>
		/// �����_�[�I�u�W�F�N�g��ǉ�
		/// </summary>
		/// <param name="modelRender"></param>
		void AddFontRenderObject(FontRender* renderObject)
		{
			m_fontList.emplace_back(renderObject);
		}

		LightCB& GetLightCB()
		{
			return m_lightCB;
		}

		DirectionLight::directionLight& GetDirectionLight()
		{
			return m_directionLig.GetDirectionLig();
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

		void SetAmbient(const float amb)
		{
			m_directionLig.SetAmbientLight(amb);
			GetLightCB().directionLig = m_directionLig.GetDirectionLig();
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
		/// 2D�����_�[�^�[�Q�b�g��������
		/// </summary>
		void Init2DRenderTarget();

		/// <summary>
		/// ���f���̕`��
		/// </summary>
		/// <param name="rc"></param>
		void ModelRendering(RenderContext& rc);
		/// <summary>
		/// 2D�`�揈��
		/// </summary>
		/// <param name="rc"></param>
		void Render2D(RenderContext& rc);
		/// <summary>
		/// �t�H���g�̕`��
		/// </summary>
		/// <param name="rc"></param>
		void FontRendering(RenderContext& rc);
	private:
		static RenderingEngine*		m_instance;							//���C�g�p�̍\����
		
		DirectionLight				m_directionLig;						//�f�B���N�V���i�����C�g�̍\����
		LightCB						m_lightCB;


		RenderTarget				m_mainRenderTarget;					//���C�������_�[�^�[�Q�b�g
		RenderTarget				m_2DRenderTarget;					//2D�����_�[�^�[�Q�b�g
		Sprite						m_2DSprite;							//2D�X�v���C�g
		Sprite						m_mainSprite;
		std::vector<SpriteRender*>  m_spriteList;						//�����_�����O����I�u�W�F�N�g
		std::vector<ModelRender*>	m_modeList;							//���f�����X�g
		std::vector<FontRender*>	m_fontList;							//�t�H���g���X�g
	};
}


