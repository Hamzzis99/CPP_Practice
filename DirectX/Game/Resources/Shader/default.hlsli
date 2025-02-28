// default.hlsli
// GPU에게 외주를 받는 것.

//float4 그냥 float가 네 개 있다는 것?

cbuffer TEST_B0 : register(b0)
{
    float4 offset0;
};

cbuffer TEST_B1 : register(b1)
{
    float4 offset1;
};

struct VS_IN
{
    float3 pos : POSITION;
    float4 color : COLOR;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float4 color : COLOR;
};

VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;

    output.pos = float4(input.pos, 1.f);
    output.pos += offset0; // 따로 넘겨준 인자로부터 변화를 주는 것.
    output.color = input.color;
    output.color += offset1; // 따로 넘겨준 인자로부터 변화를 주는 것.

    return output;
}

float4 PS_Main(VS_OUT input) : SV_Target
{
    return input.color;
}