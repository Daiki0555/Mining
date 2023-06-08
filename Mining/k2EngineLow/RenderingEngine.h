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
		void AddSpriteRenderObject(SpriteRender* renderObject)
		{
			m_spriteList.push_back(renderObject);
		}

		/// <summary>
		/// レンダーオブジェクトを追加
		/// </summary>
		/// <param name="modelRender"></param>
		void AddModelRenderObject(ModelRender* renderObject)
		{
			m_modeList.push_back(renderObject);
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
		/// <summary>
		/// 2Dレンダーターゲットを初期化
		/// </summary>
		void Init2DRenderTarget();


		/// <summary>
		/// 2D描画処理
		/// </summary>
		/// <param name="rc"></param>
		void Render2D(RenderContext& rc);
	private:
		static RenderingEngine*		m_instance;							//ライト用の構造体
		RenderTarget				m_mainRenderTarget;					//メインレンダーターゲット
		RenderTarget				m_2DRenderTarget;					//2Dレンダーターゲット
		Sprite						m_2DSprite;							//2Dスプライト
		Sprite						m_mainSprite;
		std::vector<SpriteRender*>  m_spriteList;					//レンダリングするオブジェクト
		std::vector<ModelRender*>	m_modeList;
	};
}


