#pragma once

namespace nsK2EngineLow {
	class ModelRender;
	class SpriteRender;
	class RenderTarget;
	class RenderingEngine:public Noncopyable
	{
	public:
	private:
		RenderingEngine();
		~RenderingEngine();

		void ModelRendering(RenderContext& rc);

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
			m_spriteList.push_back(renderObject);
		}

		/// <summary>
		/// �����_�[�I�u�W�F�N�g��ǉ�
		/// </summary>
		/// <param name="modelRender"></param>
		void AddModelRenderObject(ModelRender* renderObject)
		{
			m_modeList.push_back(renderObject);
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
		/// 2D�`�揈��
		/// </summary>
		/// <param name="rc"></param>
		void Render2D(RenderContext& rc);
	private:
		static RenderingEngine*		m_instance;							//���C�g�p�̍\����
		RenderTarget				m_mainRenderTarget;					//���C�������_�[�^�[�Q�b�g
		RenderTarget				m_2DRenderTarget;					//2D�����_�[�^�[�Q�b�g
		Sprite						m_2DSprite;							//2D�X�v���C�g
		Sprite						m_mainSprite;
		std::vector<SpriteRender*>  m_spriteList;					//�����_�����O����I�u�W�F�N�g
		std::vector<ModelRender*>	m_modeList;
	};
}


