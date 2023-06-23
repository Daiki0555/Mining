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

//半球ライト
struct HemiLig
{
	float3 groundColor;			//照り返しのライト
	float3 skyColor;			//天球ライト
	float3 groundNormal;		//地面の法線
};

//シャドウマップ
struct Shadow
{
	float3 ligthPos;			//ライトの座標
	float4x4 mLVP;				//ライトビュープロプロジェクション行列
};

cbuffer LightCb:register(b1){
	DirectionLig dirLig;		//ディレクションライト用の定数バッファー
	PointLig ptLig[2];			//ポイントライトの定数バッファー
	SpotLig spLig[1];			//スポットライトの定数バッファー
	HemiLig hemiLig;			//半球ライトの定数バッファー
	Shadow shadow;
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
	float3 tangent	: TANGENT;		//接ベクトル
	float3 biNormal	: BINORMAL;		//従ベクトル
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 		: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float2 uv 		: TEXCOORD0;	//uv座標。
	float3 normal	: NORMAL;		//法線
	float3 worldPos : TEXCOORD1;
	float3 normalInView: TEXCOORD2;	//カメラ空間の法線

	float3 tangent	: TANGENT;		//接ベクトル
	float3 biNormal	: BINORMAL;		//従ベクトル

	float4 posInLVP : TEXCOORD3;	//ライトビュースクリーン空間でのピクセルの座標
	float4 worldPos2 : TEXCOORD4;

};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。
Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);
Texture2D<float4> g_shadowMap : register(t10);
////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);
float3 CalcLigFromPointLight(SPSIn psIn, float3 normal);
float3 CalcLigFromSpotLight(SPSIn psIn, float3 normal);
float CalcLim(float3 dirDirection, float3 normal, float3 normalInView);
float3 CalcLigFromHemiSphereLight(float3 normal,float3 groundColor, float3 skyColor, float3 groundNormal);
float3 CalcNormal(SPSIn psIn);
float3 CalcSpecular(float2 uv);
float4 ShadowMap(float4 posInLVP, float4 albedo);
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
	float4 worldPos = mul(m, vsIn.pos);
	//ライトビュースクリーン空間の座標を計算する
	psIn.posInLVP = mul(shadow.mLVP, worldPos);
	//psIn.posInLVP.w = 50.0f;
	psIn.worldPos = worldPos;
	psIn.pos = mul(mView, worldPos);
	psIn.pos = mul(mProj, psIn.pos);

	//頂点法線をピクセルシェーダーに渡す
	psIn.normal =normalize(mul(m, vsIn.normal));	//法線を回転させる

	//接ベクトルと従ベクトルをワールド空間に変換する
	psIn.tangent=normalize(mul(m,vsIn.tangent));
	psIn.biNormal=normalize(mul(m,vsIn.biNormal));

	

	psIn.uv = vsIn.uv;

	//カメラ空間の法線を求める
	psIn.normalInView=mul(mView,psIn.normal);

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
float4 PSMainCore( SPSIn psIn,uniform bool hasShadow) : SV_Target0
{
	//アルベドマップを読み込む
    float4 albedo = g_albedo.Sample(g_sampler, psIn.uv);
	albedo.a = 1.0f;
	//法線によるライティングを計算する
	float3 normalMap=CalcNormal(psIn);
	//スペキュラマップを計算する
	float specMap=CalcSpecular(psIn.uv);
	//ディレクションライトによるLambert拡散反射光を計算する
	float3 diffDirection=CalcLambertDiffuse(dirLig.ligDirection,dirLig.ligColor,normalMap);
	// ディレクションライトによるPhong鏡面反射光を計算する
	float3 specuDirection=CalcPhongSpecular(dirLig.ligDirection,dirLig.ligColor,psIn.worldPos,normalMap);
	specuDirection*=specMap;
	//ポイントライトによるライティングを計算する
	float3 pointLight=CalcLigFromPointLight(psIn,normalMap); 
	//スポットライトによるライティングを計算する
	float3 spotLight=CalcLigFromSpotLight(psIn,normalMap);
	//リムライトによるライティングを計算する
	float limLight=CalcLim(dirLig.ligDirection,normalMap,psIn.normalInView);
	//半球ライトによるライティングを計算する
	float3 hemiSphereLight=CalcLigFromHemiSphereLight(normalMap,hemiLig.groundColor, hemiLig.skyColor, hemiLig.groundNormal);

	
	//最終的な反射光にリムライトの反射光を合算する
	float3 limColor=limLight*dirLig.ligColor;



	
	//すべてを足して最終的な光を求める
	float3 lig = diffDirection
				+specuDirection
				+dirLig.ambient
				+pointLight
				+spotLight
				+limColor
				+hemiSphereLight;

	lig=min(lig,10.0f);

	if(hasShadow){
		albedo=ShadowMap(psIn.posInLVP,albedo);
	}
	
	albedo.xyz*= lig;
	
	return albedo;
}

/// <summary>
/// シャドウ無しのエントリー関数。
/// </summary>
float4 PSMain( SPSIn psIn ) : SV_Target0
{
	return PSMainCore(psIn, false);
}

/// <summary>
/// シャドウ有りのエントリー関数。
/// </summary>
float4 PSMainShadow( SPSIn psIn ) : SV_Target0
{
	return PSMainCore(psIn, true);
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
float3 CalcLigFromPointLight(SPSIn psIn, float3 normal)
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
			normal
		);

		//減衰なしのPhong鏡面反射光を計算する
		float3 specPoint=CalcPhongSpecular(
			ligDir,
			ptLig[i].ptColor,
			psIn.worldPos,
			normal
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

/// <summary>
/// スポットライトを計算する
/// </summary>
float3 CalcLigFromSpotLight(SPSIn psIn, float3 normal)
{
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
			normal				//サーフェイスの法線
		);

		//減衰なしのPhong鏡面反射を計算する
		float3 specSpotLight=CalcPhongSpecular(
			ligDir,				//ライトの方向	
			spLig[i].spColor,	//ライトのカラー
			psIn.worldPos,		//サーフェイスのワールド座標
			normal				//サーフェイスの法線
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
	return finalspLig;
}

/// <summary>
/// リムライトを計算する
/// </summary>
float CalcLim(float3 dirDirection, float3 normal, float3 normalInView)
{
	//サーフェイスの法線と光の入射方向に依存するリムの強さを求める
	float power1=1.0f-max(0.0f,dot(dirDirection,normal));

	//サーフェイスの法線と視線の方向に依存するリムの強さを求める
	float power2=1.0f-max(0.0f,normalInView.z*-1.0f);

	//最終的なリムの強さを求める
	float limPower=power1*power2;

	//pow()関数を使用して、強さの変化を指数関数的にする
	limPower=pow(limPower,3.0f);


	return limPower;
}

/// <summary>
/// 半球ライトを計算する
/// </summary>
float3 CalcLigFromHemiSphereLight(float3 normal,float3 groundColor, float3 skyColor, float3 groundNormal)
{
	//半球ライトを計算する
	//サーフェイスの法線と地面の法線との内積を計算する
	float t=dot(normal,groundNormal);

	//内積の結果を0～１の範囲に変換する
	t=(t+1.0f)/2.0f;

	//地面色と天球色を補完率tで線形補間する
	float3 hemiLight=lerp(groundColor,skyColor,t);

	return hemiLight;

}

/// <summary>
/// 法線を計算する
/// </summary>
float3 CalcNormal(SPSIn psIn)
{
	//法線マップからタンジェントスペースの法線をサンプリングする
	float3 localNormal=g_normalMap.Sample(g_sampler,psIn.uv).xyz;
	//タンジェントスペースの法線を0～１の範囲から-1～１の範囲に復元する
	localNormal=(localNormal-0.5f)*2.0f;


	//タンジェントスペースの法線をワールドスペースに変換する
	float3 newNormal = psIn.tangent * localNormal.x
				   + psIn.biNormal * localNormal.y
				   + psIn.normal * localNormal.z;

	if(isnan(newNormal.x)){
		newNormal = (0.0f, 0.0f, 0.0f);
	}

	newNormal.x = min(max(newNormal.x,-1.0f),1.0f);
	newNormal.y = min(max(newNormal.y,-1.0f),1.0f);
	newNormal.z = min(max(newNormal.z,-1.0f),1.0f);
	
	return newNormal;

}

/// <summary>
/// スペキュラを計算
/// </summary>
float3 CalcSpecular(float2 uv)
{
		//スペキュラマップからスペキュラ反射をサンプリング
	float specPower=g_specularMap.Sample(g_sampler,uv).r;

	return specPower*10.0f;
}

float4 ShadowMap(float4 posInLVP, float4 albedo)
{
	//ライトビュースクリーン空間の座標からUV空間に座標変換
	//ライトビュースクリーン空間からUV座標空間に変換している
	float2 shadowMapUV=posInLVP.xy/posInLVP.w;
	shadowMapUV*=float2(0.5f,-0.5f);
	shadowMapUV+=0.5f;

	//ライトビュースクリーン空間でのZ値を計算する
	float zInLVP=posInLVP.z/posInLVP.w;

	//UV座標を使ってシャドウマップから影情報をサンプリング
	if(shadowMapUV.x>0.0f&&shadowMapUV.x<1.0f
	&&shadowMapUV.y>0.0f&&shadowMapUV.y<1.0f)
	{
		//シャドウマップに書き込まれているZ値と比較する
		//計算したUV座標を使って、シャドウマップから深度値をサンプリング
		float zInshadowMap=g_shadowMap.Sample(g_sampler,shadowMapUV).r;
		if(zInLVP>zInshadowMap)
		{
			//遮蔽されている
			albedo.xyz*=0.5f;

		}
	}
	//return zInLVP;
	return albedo;


}
