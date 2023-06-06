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
			if (m_instance == nullptr) {
				CreateInstance();
			}

			return m_instance;
		}
		/// <summary>
		/// レンダーオブジェクトを追加
		/// </summary>
		/// <param name="modelRender"></param>
		void AddRenderObject(ModelRender* modelRender)
		{
			m_modelList.push_back(modelRender);
		}


		/// <summary>
		/// 初期化処理
		/// </summary>
		void Init();

		/// <summary>
		/// 実行処理
		/// </summary>
		/// <param name="rc"></param>
		void Execute(RenderContext& rc);
	private:
		static RenderingEngine*		m_instance;
		RenderTarget				m_mainRenderTarget;
		std::vector<ModelRender*>	m_modelList;
	};
}


