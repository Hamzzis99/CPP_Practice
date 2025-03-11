#ifndef _DEFAULT_HLSLI_
#define _DEFAULT_HLSLI_

#include "params.hlsli" //쉐이더 문법이 아닌 비주얼 스튜디오가 처리해주는 것.
#include "utils.hlsli"

struct VS_IN // 로컬을 기준으로 
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};

struct VS_OUT
{
    float4 pos : SV_Position; // Systeam Value 예약된 이름 그냥 float4해라. 마소가 그랬잖냐.
    float2 uv : TEXCOORD;
    
    //아래에있는 viewpos viewnormal은 조명을 쏘는 
    float3 viewPos : POSITION; // 뷰 좌표계의 포지션
    float3 viewNormal : NORMAL; // 뷰 포지션의 노말벡터
    float3 viewTangent : TANGENT;
    float3 viewBinormal : BINORMAL;
};

VS_OUT VS_Main(VS_IN input) 
{
    VS_OUT output = (VS_OUT) 0;

    // float4를 곱해준 다음에 matwvp와 계산하여 행렬을 구해준다. 
    // 1의 의미는 그냥 좌표의 방향성.
    output.pos = mul(float4(input.pos, 1.f), g_matWVP); // input.pos에 있는 WVP를 쭉 곱하게 되면 투영 좌표계로 넘김.
    output.uv = input.uv;

    //아래에 있는 것은 viewspace 기준의 좌표들이다.
    output.viewPos = mul(float4(input.pos, 1.f), g_matWV).xyz; // 바로 투영좌표까지 가진 않고 WV까지 가고 끊은 뒤에 빛을 계산해주는 것.
    output.viewNormal = normalize(mul(float4(input.normal, 0.f), g_matWV).xyz);
    output.viewTangent = normalize(mul(float4(input.tangent, 0.f), g_matWV).xyz);
    output.viewBinormal = normalize(cross(output.viewTangent, output.viewNormal)); // Tangent Normal Binormal
    return output;
}

float4 PS_Main(VS_OUT input) : SV_Target // 픽셀 단위로 작업을 해주고 계산하는 것.
{
    float4 color = float4(1.f, 1.f, 1.f, 1.f);
    if (g_tex_on_0)
        color = g_tex_0.Sample(g_sam_0, input.uv);
    
    float3 viewNormal = input.viewNormal;
    if (g_tex_on_1)
    {
        // [0,255] 범위에서 [0,1]로 변환
        float3 tangentSpaceNormal = g_tex_1.Sample(g_sam_0, input.uv).xyz; // xyz 추출하여 탄젠트 스페이스 노말이라 부르게 한다.
        // [0,1] 범위에서 [-1,1]로 변환
        tangentSpaceNormal = (tangentSpaceNormal - 0.5f) * 2.f; // RGB -1 ~ 1 조절
        
        // 노멀맵핑 TBN 좌표 구하기.
        float3x3 matTBN = { input.viewTangent, input.viewBinormal, input.viewNormal };
        viewNormal = normalize(mul(tangentSpaceNormal, matTBN));
    }
    
    // float4 color = g_tex_0.Sample(g_sam_0, input.uv); //uv를 이용하여 컬러를 계산하는중.
    //float4 color = float4(1.f, 1.f, 1.f, 1.f);

    LightColor totalColor = (LightColor) 0.f; // 각각에 있는 정보들을 계산을 한다.

    // 빛이라는 것은 정해진 것이 없다. 이뻐 보이면 된다. 우선 아래가 일반적인 식.
    
    for (int i = 0; i < g_lightCount; ++i) // 내가들고있는 조명을 하나하나 다 순회를 하고
    {
        LightColor color = CalculateLightColor(i, input.viewNormal, input.viewPos); //광원 하나에 대한 색상. 아래있는 3대요소가 합해져서 뱉어내는 것.
        totalColor.diffuse += color.diffuse;
        totalColor.ambient += color.ambient;
        totalColor.specular += color.specular;
    }

    // 곱해가지고 최종 색상을 구해주는 것.
    color.xyz = (totalColor.diffuse.xyz * color.xyz)
        + totalColor.ambient.xyz * color.xyz
        + totalColor.specular.xyz;

    return color;
}

#endif