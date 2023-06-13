/*!
 * @brief	シンプルなモデルシェーダー。
 */


////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

//ディレクションライト用の構造体
struct DirectionLig
{
	float3 ligDirection;		//ライトの方向
	float3 ligColor;			//ライトのカラー
	float3 eyePos;				//視点の位置
	float3 ambient;
};


cbuffer LightCb:register(b1){
	DirectionLig dirLig;		//ディレクションライト用の定数バッファー
};

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float2 uv 		: TEXCOORD0;	//UV座標。
	float3 normal	: NORMAL;		//法線
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 		: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float2 uv 		: TEXCOORD0;	//uv座標。
	float3 normal	: NORMAL;		//法線
	float3 worldPos : TEXCOORD1;
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////

/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;
	float4x4 m;
	if( hasSkin ){
		m = CalcSkinMatrix(vsIn.skinVert);
	}else{
		m = mWorld;
	}
	psIn.pos = mul(m, vsIn.pos);
	psIn.worldPos = vsIn.pos;
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

	//頂点法線をピクセルシェーダーに渡す
	psIn.normal =mul(m, vsIn.normal);	//法線を回転させる

	psIn.uv = vsIn.uv;

	return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}
/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain( SPSIn psIn ) : SV_Target0
{
	//ピクセルの法線とライトの方向の内積を計算する
	float t = dot(psIn.normal, dirLig.ligDirection);
    t *= -1.0f;

	//内積の結果が０以下なら０にする
	t=max(t,0.0f);

	//ピクセルが受けている光を求める
	float3 diffuseLig=dirLig.ligColor * t;

	//反射ベクトルを求める
	float3 refVec = reflect(dirLig.ligDirection, psIn.normal);

	//光が当たったサーフェイスから視点に伸びるベクトルを求める
	 float3 toEye = dirLig.eyePos - psIn.worldPos;

	//正規化する
	toEye = normalize(toEye);

	//dot関数を利用してrefVecとtoEyeの内積を求める
	t=dot(refVec,toEye);

	//マイナスの場合は0にする
	t=max(t,0.0f);

	//鏡面反射の強さを絞る
	t=pow(t,5.0f);

	//鏡面反射光を求める
	 float3 specularLig = dirLig.ligColor * t;

	//拡散反射光と鏡面反射光を足して最終的な光を求める
	float3 lig = diffuseLig + specularLig;

	lig.x+=dirLig.ambient;
	lig.x=min(lig.x,1.0f);
	lig.y+=dirLig.ambient;
	lig.y=min(lig.y,1.0f);
	lig.z+=dirLig.ambient;
	lig.z=min(lig.z,1.0f);



	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);
	
	albedoColor.xyz*= lig;
	
	return albedoColor;
}
