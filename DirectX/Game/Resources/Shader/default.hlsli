
cbuffer TRANSFORM_PARAMS : register(b0) // Transform과 관련된 것을 넣은 것.
{
    //row_major -> 쉐이더 행렬 접근을 다이렉트 규칙으로 해준다는 뜻. (맞나?)
    row_major matrix matWVP; // 매트릭스인데 이름은 WVP라는 것.
};

cbuffer MATERIAL_PARAMS : register(b1) // 머테리얼에게 전달할 값들.
{
    int int_0;
    int int_1;
    int int_2;
    int int_3;
    int int_4;
    float float_0;
    float float_1;
    float float_2;
    float float_3;
    float float_4;
};

Texture2D tex_0 : register(t0);
Texture2D tex_1 : register(t1);
Texture2D tex_2 : register(t2);
Texture2D tex_3 : register(t3);
Texture2D tex_4 : register(t4);

SamplerState sam_0 : register(s0);

struct VS_IN
{
    float3 pos : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;

    // float4를 곱해준 다음에 matwvp와 계산하여 행렬을 구해준다. 
    // 1의 의미는 그냥 좌표의 방향성.
    output.pos = mul(float4(input.pos, 1.f), matWVP); 
    output.color = input.color;
    output.uv = input.uv;

    return output;
}

float4 PS_Main(VS_OUT input) : SV_Target
{
    float4 color = tex_0.Sample(sam_0, input.uv);
    return color;
}