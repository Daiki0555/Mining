#pragma once

namespace nsK2EngineLow {
	class ModelRender;
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
		void AddRenderObject(ModelRender* modelRender)
		{
			m_modelList.push_back(modelRender);
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
		static RenderingEngine*		m_instance;
		RenderTarget				m_mainRenderTarget;
		std::vector<ModelRender*>	m_modelList;
	};
}


