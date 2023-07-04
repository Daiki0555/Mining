#pragma once
namespace nsK2EngineLow
{
	class Bloom
	{
	public:
		struct LuminanceCB
		{
			float threshold = 1.0f;	//臒l
		};
	public:
		Bloom();
		~Bloom();

		/// <summary>
		/// �u���[������������臒l��ݒ�
		/// </summary>
		/// <param name="threshold">臒l</param>
		void SetThreshold(float threshold)
		{
			m_luminanceCB.threshold = threshold;
		}

		/// <summary>
		/// �u���[������������臒l���擾
		/// </summary>
		/// <returns></returns>
		float GetThreshold() const
		{
			return m_luminanceCB.threshold;
		}

		/// <summary>
		/// �|�X�g�G�t�F�N�g�����s�������ʂƂȂ�e�N�X�`�����擾�B
		/// </summary>
		/// <returns></returns>
		Texture& GetResultTexture()
		{
			return m_luminanceRenderTarget.GetRenderTargetTexture();
		}

		/// <summary>
		/// ����������
		/// </summary>
		/// <param name="mainRenderTarget"></param>
		void Init(RenderTarget& mainRenderTarget);


		void Render(RenderContext& rc, RenderTarget& mainRenderTarget);

	private:
		RenderTarget m_luminanceRenderTarget;
		LuminanceCB m_luminanceCB;
		GaussianBlur m_gaussianBlur[4];
		Sprite m_finalSprite;
		Sprite m_luminanceSprite;

		Sprite m_copyMainRtSprite;				//���C�������_�����O�^�[�Q�b�g�ɕ`�悷�邽�߂̃X�v���C�g
	};
}


