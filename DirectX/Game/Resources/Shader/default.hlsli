#ifndef _DEFAULT_HLSLI_
#define _DEFAULT_HLSLI_

#include "params.hlsli" //���̴� ������ �ƴ� ���־� ��Ʃ����� ó�����ִ� ��.

struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct VS_OUT
{
    float4 pos : SV_Position; // Systeam Value ����� �̸� �׳� float4�ض�. ���Ұ� �׷��ݳ�.
    float2 uv : TEXCOORD;
    float viewPos : SV_Position; // �� ��ǥ���� ������
    float3 viewNormal : NORMAL; // �� �������� �븻����
};

VS_OUT VS_Main(VS_IN input) 
{
    VS_OUT output = (VS_OUT) 0;

    // float4�� ������ ������ matwvp�� ����Ͽ� ����� �����ش�. 
    // 1�� �ǹ̴� �׳� ��ǥ�� ���⼺.
    output.pos = mul(float4(input.pos, 1.f), g_matWVP); // input.pos�� �ִ� WVP�� �� ���ϰ� �Ǹ� ���� ��ǥ��� �ѱ�.
    output.uv = input.uv;

    output.viewPos = mul(float4(input.pos, 1.f), g_matWV).xyz; // �ٷ� ������ǥ���� ���� �ʰ� WV���� ���� ���� �ڿ� ���� ������ִ� ��.
    output.viewNormal = normalize(mul(float4(input.normal, 0.f), g_matWV).xyz);
    
    return output;
}

float4 PS_Main(VS_OUT input) : SV_Target // �ȼ� ������ �۾��� ���ְ� ����ϴ� ��.
{
    float4 color = tex_0.Sample(g_sam_0, input.uv); //uv�� �̿��Ͽ� �÷��� ����ϴ���.
    return color;
}

#endif