/*!
 * @brief	�X�v���C�g�p�̃V�F�[�_�[�B
 */

cbuffer cb : register(b0){
	float4x4 mvp;		//���[���h�r���[�v���W�F�N�V�����s��B
	float4 mulColor;	//��Z�J���[�B
};

cbuffer SpriteCB:register(b1)
{
	float Angle;		// 角度
}

struct VSInput{
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);	//�J���[�e�N�X�`���B
sampler Sampler : register(s0);

static const float PI = 3.14159f;			// 円周率
static const float2 CENTER = (0.5f, 0.5f);	// 円の中央

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain( PSInput In ) : SV_Target0
{
	return colorTexture.Sample(Sampler, In.uv) * mulColor;
}

// 円形ゲージの計算
float4 PSCircleGauge(PSInput In) :Sv_Target0
{
	// 中心から上方向のベクトル
	float2 Vector1 = {0.0f,-1.0f};
	// 中心からピクセルの座標へのベクトル
	float2 Vector2 = In.uv - CENTER;
	// 正規化
	Vector1 = normalize(Vector1);
	Vector2 = normalize(Vector2);

	// 2つのベクトルの内積の逆正弦を計算する
	float Deg = acos(dot(Vector1, Vector2));
	// 絶対値を計算
	Deg = abs(Deg);

	// 角度を計算
	if(Vector2.x > Vector1.x){
		Deg = PI + (PI + Deg);
	}

	// 設定した角度より大きいなら
	if(Deg >= Angle){
		// ピクセルを破棄
		clip(-1);
	}

	return colorTexture.Sample(Sampler, In.uv);
}