#pragma once
namespace nsK2EngineLow {
	/// <summary>
	/// レンダラーの基底クラス
	/// </summary>
	class IRenderer {
	public:

		virtual void OnRenderModel(RenderContext& rc)
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
