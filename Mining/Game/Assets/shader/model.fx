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
	float3 ambient;				//環境光の強さ
};

//ポイントライト用の構造体
struct PointLig
{
	float3 ptPosition;			//ポイントライトの位置
	float3 ptColor;				//ポイントライトのカラー
	float  ptRange;				//ポイントライトの影響範囲
};

//スポットライト用の構造体
struct SpotLig
{
	float3 spPosition;			//スポットライトの位置
	float3 spColor;				//スポットライトのカラー	
	float spRange;				//スポットライトの射出範囲
	float3 spDirection;			//スポットライトの射出方向
	float spAngle;				//スポットライトの射出角度

};

cbuffer LightCb:register(b1){
	DirectionLig dirLig;		//ディレクションライト用の定数バッファー
	PointLig ptLig[2];			//ポイントライトの定数バッファー
	SpotLig spLig[1];			//スポットライトの定数バッファー
	int ptNum;					//ポイントライトの数
	int spNum;
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
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);
float3 CalcLigFromPointLight(SPSIn psIn);
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
	psIn.worldPos = psIn.pos;
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
	//ディレクションライトによるLambert拡散反射光を計算する
	float3 diffDirection=CalcLambertDiffuse(dirLig.ligDirection,dirLig.ligColor,psIn.normal);
	// ディレクションライトによるPhong鏡面反射光を計算する
	float3 specuDirection=CalcPhongSpecular(dirLig.ligDirection,dirLig.ligColor,psIn.worldPos,psIn.normal);
	//ポイントライトによるライティングを計算する
	float3 pointLight=CalcLigFromPointLight(psIn); 

	float3 finalspLig = (0.0f, 0.0f, 0.0f);
	//スポットライトによるライティングを計算する
	for(int i=0;i<spNum;i++)
	{
		//ピクセル座標ースポットライトの座標を計算
		float3 ligDir=psIn.worldPos-spLig[i].spPosition;

		//正規化して大きさ1のベクトルにする
		ligDir=normalize(ligDir);

		//減衰なしのLambert拡散反射光を計算する
		float3 diffSpotLight=CalcLambertDiffuse(
			ligDir,				//ライトの方向
			spLig[i].spColor,	//ライトのカラー
			psIn.normal			//サーフェイスの法線
		);

		//減衰なしのPhong鏡面反射を計算する
		float3 specSpotLight=CalcPhongSpecular(
			ligDir,				//ライトの方向	
			spLig[i].spColor,	//ライトのカラー
			psIn.worldPos,		//サーフェイスのワールド座標
			psIn.normal			//サーフェイスの法線
		);
		//距離による影響率を計算する
    	// スポットライトとの距離を計算する
		float3 distance =length(psIn.worldPos-spLig[i].spPosition);

		//影響率は距離に比例して小さくなっていく
		float affect =1.0f-1.0f/spLig[i].spRange*distance;
		affect=max(affect,0.0f);

		//影響率を指数関数的にする
		affect=pow(affect,3.0f);

		//影響率を乗算して反射光を弱める
		diffSpotLight*=affect;
		specSpotLight*=affect;

		//入射光と射出方向の角度を求める
    	//dot()を利用して内積を求める
		float angle=dot(ligDir,spLig[i].spDirection);

		//dot()で求めた値をacos()に渡して角度を求める
		angle=abs(acos(angle));

		 // 角度による影響率を求める
    	// 角度に比例して小さくなっていく影響率を計算する
    	affect = 1.0f - 1.0f / spLig[i].spAngle * angle;
		affect=max(affect,0.0f);

		// 影響の仕方を指数関数的にする。
    	affect = pow(affect, 0.5f);

		diffSpotLight*=affect;
		specSpotLight*=affect;

		finalspLig=diffSpotLight+specSpotLight;
	}
	

	//拡散反射光と鏡面反射光を足して最終的な光を求める
	float3 lig = finalspLig+diffDirection+specuDirection+dirLig.ambient+pointLight;

	lig=min(lig,10.0f);

	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);
	
	albedoColor.xyz*= lig;
	
	return albedoColor;
}

/// <summary>
/// Lambert拡散反射光を計算する
/// </summary>
float3 CalcLambertDiffuse(float3 lightDirection,float3 lightColor,float3 normal)
{
	//ピクセルの法線とライト方向の内積を計算する
	float t=dot(normal,lightDirection)*-1.0f;

	//内積の値を0以上の値にする
	t=max(t,0.0f);

	//拡散反射光を計算する
	return lightColor*t;
} 

/// <summary>
/// Phong鏡面反射光を計算する
/// </summary>
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
	//反射ベクトルを求める
	float3 refVec=reflect(lightDirection,normal);

	//光があたったサーフェイスから視点に伸びるベクトルを求める
	float3 toEye=dirLig.eyePos-worldPos;

	//正規化する
	toEye=normalize(toEye);

	//鏡面反射光の強さを求める
	float t=dot(refVec,toEye);

	t=max(t,0.0f);

	//鏡面反射の強さを求める
	t=pow(t,2.0f);

	//鏡面反射光を求める
	return lightColor*t;

}

/// <summary>
/// ポイントライトによる反射光を計算
/// </summary>
/// <param name="psIn">ピクセルシェーダーに渡されている引数</param>
float3 CalcLigFromPointLight(SPSIn psIn)
{
	float3 finalPtLig = (0.0f, 0.0f, 0.0f);

	for(int i=0;i<ptNum;i++)
	{
		//ポイントライトによるLambert拡散反射光とPhong鏡面反射光を計算する
		//サーフェイスに入射するポイントライトの光の向きを計算する
		
		float3 ligDir=psIn.worldPos-ptLig[i].ptPosition;
		ligDir = normalize(ligDir);
		//減衰なしのLambert拡散反射光を計算する
		float3 diffPoint=CalcLambertDiffuse(
			ligDir,
			ptLig[i].ptColor,
			psIn.normal
		);

		//減衰なしのPhong鏡面反射光を計算する
		float3 specPoint=CalcPhongSpecular(
			ligDir,
			ptLig[i].ptColor,
			psIn.worldPos,
			psIn.normal
		);
		
		//ポイントライトとの距離を計算する
		float distance=length(psIn.worldPos-ptLig[i].ptPosition);

		//影響率は距離に比例して小さくなっていく
		float affect=1.0f-1.0f/ptLig[i].ptRange*distance;
		affect=max(affect,0.0f);

		//影響率を指数関数的にする
		affect=pow(affect,3.0f);

		//拡散反射光と鏡面反射光に減衰率を乗算して影響率を弱める
		diffPoint*=affect;
		specPoint*=affect;
	 	finalPtLig += diffPoint + specPoint;
	}
	return finalPtLig;
}