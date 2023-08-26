#pragma once
namespace nsK2EngineLow {
	/// <summary>
	/// レンダラーの基底クラス
	/// </summary>
	class IRenderer {
	public:
		
		
		/// <summary>
		/// フォワードレンダリング
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト</param>
		virtual void OnRenderModel(RenderContext& rc)
		{

		}
		/// <summary>
		/// シャドウマップへの描画パスから呼ばれる処理。
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト</param>
		/// <param name="camera">カメラ</param>
		virtual void OnRenderShadowMap(RenderContext& rc,Camera& camera)
		{
			
		}

		/// <summary>
		/// 2D描画パスから呼ばれる処理。
		/// </summary>
		/// <param name="rc"></param>
		virtual void OnRender2D(RenderContext& rc)
		{

		}
	};

}
