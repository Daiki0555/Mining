#pragma once
namespace nsK2EngineLow {
	/// <summary>
	/// �����_���[�̊��N���X
	/// </summary>
	class IRenderer {
	public:
		
		
		/// <summary>
		/// �t�H���[�h�����_�����O
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		virtual void OnRenderModel(RenderContext& rc)
		{

		}
		/// <summary>
		/// �V���h�E�}�b�v�ւ̕`��p�X����Ă΂�鏈���B
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		/// <param name="camera">�J����</param>
		virtual void OnRenderShadowMap(RenderContext& rc,Camera& camera)
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
