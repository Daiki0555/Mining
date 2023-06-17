/*!
*@brief ブルーム
*/

cbuffer cb : register(b0)
{
    float4x4 mvp;           //MVP行列
    float4 mulColor;        //乗算カラー
};

struct VSInput
{
    float4 pos : POSITION;
    float2 uv  : TEXCOORD0;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv  : TEXCOORD0;
};

/*!
 * @brief 頂点シェーダー
 */
 PSInput VSMain(VSInput In)
 {
    PSInput psIn;
    psIn.pos=mul(mvp,In.pos);
    psIn.uv=In.uv;
    return psIn;
 }

Texture2D<float4> mainRenderTargetTexture : register(t0); //メインレンダリングターゲットのテクスチャ
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////
// 輝度抽出用
/////////////////////////////////////////////////////////
/*!
 * @brief 輝度抽出用のピクセルシェーダー
 */
 float4 PSLuminance(PSInput In) : SV_Target0
 {
    //輝度を抽出するピクセルシェーダー
    //メインレンダリングターゲットからカラーをサンプリング
    float4 color=mainRenderTargetTexture.Sample(Sampler,In.uv);

    //サンプリングしたカラーの明るさを計算
    float t=dot(color.xyz,float3(0.2125f,0.7154f,0.0721f));

    //clip()関数は引数がマイナスになると、以降の処理をスキップする
    //なのでマイナスになるとピクセルカラーは出力されない
    //カラーがの明るさが1以下ならピクセルキルをする
    clip(t-1.0f);
    return color;
 }