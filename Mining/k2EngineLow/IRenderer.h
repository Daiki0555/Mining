#pragma once
namespace nsK2EngineLow {
	/// <summary>
	/// �����_���[�̊��N���X
	/// </summary>
	class IRenderer {
	public:

		virtual void OnRenderModel(RenderContext& rc)
		{

		}

		/// <summary>
		/// 2D�`��p�X����Ă΂�鏈���B
		/// </summary>
		/// <param name="rc"></param>
		virtual void OnRender2D(RenderContext& rc)
		{

		}
	};

}
