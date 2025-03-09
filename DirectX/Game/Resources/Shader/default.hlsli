#ifndef _DEFAULT_HLSLI_
#define _DEFAULT_HLSLI_

#include "params.hlsli" //쉐이더 문법이 아닌 비주얼 스튜디오가 처리해주는 것.

struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct VS_OUT
{
    float4 pos : SV_Position; // Systeam Value 예약된 이름 그냥 float4해라. 마소가 그랬잖냐.
    float2 uv : TEXCOORD;
    float viewPos : SV_Position; // 뷰 좌표계의 포지션
    float3 viewNormal : NORMAL; // 뷰 포지션의 노말벡터
};

VS_OUT VS_Main(VS_IN input) 
{
    VS_OUT output = (VS_OUT) 0;

    // float4를 곱해준 다음에 matwvp와 계산하여 행렬을 구해준다. 
    // 1의 의미는 그냥 좌표의 방향성.
    output.pos = mul(float4(input.pos, 1.f), g_matWVP); // input.pos에 있는 WVP를 쭉 곱하게 되면 투영 좌표계로 넘김.
    output.uv = input.uv;

    output.viewPos = mul(float4(input.pos, 1.f), g_matWV).xyz; // 바로 투영좌표까지 가진 않고 WV까지 가고 끊은 뒤에 빛을 계산해주는 것.
    output.viewNormal = normalize(mul(float4(input.normal, 0.f), g_matWV).xyz);
    
    return output;
}

float4 PS_Main(VS_OUT input) : SV_Target // 픽셀 단위로 작업을 해주고 계산하는 것.
{
    float4 color = tex_0.Sample(g_sam_0, input.uv); //uv를 이용하여 컬러를 계산하는중.
    return color;
}

#endif