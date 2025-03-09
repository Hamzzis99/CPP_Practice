//params -> 쉐이더 정보를 담은 것.
#ifndef _PARAMS_HLSLI_ // 두 번 실행되면 안 되니까. 이걸 선언. 알잖아
#define _PARAMS_HLSLI_

struct LightColor
{
    float4 deffuse;
    float4 ambient;
    float4 specular;
};

struct LightInfo
{
    LightColor color;
    float4 position;
    float4 direction;
    int lightType;
    float range;
    float angle;
    int padding; // 페딩이란.
};


cbuffer GLOBAL_PARAMS : register(b0)
{
    int g_lightCount;
    float3 g_lightPadding;
    LightInfo g_light[50];
}

cbuffer TRANSFORM_PARAMS : register(b1) // Transform과 관련된 것을 넣은 것.
{
    //row_major -> 쉐이더 행렬 접근을 다이렉트 규칙으로 해준다는 뜻. (맞나?)
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProjection;
    row_major matrix g_matWV;
    row_major matrix matWVP; // 매트릭스인데 이름은 WVP라는 것.
};

cbuffer MATERIAL_PARAMS : register(b2) // 머테리얼에게 전달할 값들.
{
    int g_int_0;
    int g_int_1;
    int g_int_2;
    int g_int_3;
    int g_int_4;
    float g_float_0;
    float g_float_1;
    float g_float_2;
    float g_float_3;
    float g_float_4;
};

Texture2D g_tex_0 : register(t0);
Texture2D g_tex_1 : register(t1);
Texture2D g_tex_2 : register(t2);
Texture2D g_tex_3 : register(t3);
Texture2D g_tex_4 : register(t4);

SamplerState g_sam_0 : register(s0);

#endif