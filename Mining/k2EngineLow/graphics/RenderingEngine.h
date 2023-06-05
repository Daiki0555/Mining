#pragma once
#include "k2EngineLowPreCompile.h"
#include "k2EngineLow.h"
namespace nsk2EngineLow {
	class RenderingEngine
	{
	public:
	private:
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
			return m_instance;
		}
		/// <summary>
		/// ����������
		/// </summary>
		void Init();

	private:
		static RenderingEngine* m_instance;

	};
}


