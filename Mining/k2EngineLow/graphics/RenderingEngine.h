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
		/// インスタンスの生成
		/// </summary>
		static void CreateInstance()
		{
			m_instance = new RenderingEngine;
			m_instance->Init();
		}
		/// <summary>
		/// インスタンスの削除
		/// </summary>
		static void DeleteInstance()
		{
			delete m_instance;
		}
		/// <summary>
		/// インスタンスの取得
		/// </summary>
		/// <returns></returns>
		static RenderingEngine* GetInstance()
		{
			return m_instance;
		}
		/// <summary>
		/// 初期化処理
		/// </summary>
		void Init();

	private:
		static RenderingEngine* m_instance;

	};
}


