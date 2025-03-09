#ifndef _UTILS_HLSLI_
#define _UTILS_HLSLI_

LightColor CalculateLightColor(int lightIndex, float3 viewNormal, float3 viewPos)
{
    LightColor color = (LightColor)0.f;

    float3 viewLightDir = (float3)0.f;

    float diffuseRatio = 0.f;
    float specularRatio = 0.f;
    float distanceRatio = 1.f;

    if (g_light[lightIndex].lightType == 0)
    {
        // Directional L을 만들어주는 것.
        viewLightDir = normalize(mul(float4(g_light[lightIndex].direction.xyz, 0.f), g_matView).xyz);
        //saturate 음수가 나오면 무조건 0으로 만들어주는 것. 내적을 하기 위해 만들어진 것.
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));
    }
    else if (g_light[lightIndex].lightType == 1)
    {
        // Point Light 
        // viewLightPos가 고정된 값이 아님을 보임. 해당 물체에 광원의 위치를 구하는 것.
        float3 viewLightPos = mul(float4(g_light[lightIndex].position.xyz, 1.f), g_matView).xyz;
        viewLightDir = normalize(viewPos - viewLightPos);
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));

        float dist = distance(viewPos, viewLightPos);
        if (g_light[lightIndex].range == 0.f) // range가 0이 되면 빛이 없다.
            distanceRatio = 0.f; // 예외처ㅣ.
        else
            distanceRatio = saturate(1.f - pow(dist / g_light[lightIndex].range, 2)); // 빛이 점점 희미하게 만드는 것. 1보다 커지면 saturate가 0으로 바꿔줌
    }
    else
    {
        // Spot Light
        float3 viewLightPos = mul(float4(g_light[lightIndex].position.xyz, 1.f), g_matView).xyz; // 광원의 시작 위치
        viewLightDir = normalize(viewPos - viewLightPos); // 단위벡터 만들기
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));

        if (g_light[lightIndex].range == 0.f)
            distanceRatio = 0.f; // 예외체크
        else
        {
            float halfAngle = g_light[lightIndex].angle / 2; // 시야각 구하기.

            float3 viewLightVec = viewPos - viewLightPos; // 일반적으로 크기가 포함한 벡터 A벡터
            float3 viewCenterLightDir = normalize(mul(float4(g_light[lightIndex].direction.xyz, 0.f), g_matView).xyz); // 단위 벡터 L벡터

            //둘을 내적하여 빛으로 나아가는 거리를 구하는 것.
            float centerDist = dot(viewLightVec, viewCenterLightDir);
            distanceRatio = saturate(1.f - centerDist / g_light[lightIndex].range);

            float lightAngle = acos(dot(normalize(viewLightVec), viewCenterLightDir)); // 내적 해준것에 아크코사인.

            if (centerDist < 0.f || centerDist > g_light[lightIndex].range) // 최대 거리를 벗어났는지
                distanceRatio = 0.f;
            else if (lightAngle > halfAngle) // 최대 시야각을 벗어났는지
                distanceRatio = 0.f; //벗어나면 0으로.
            else // 거리에 따라 적절히 세기를 조절
                distanceRatio = saturate(1.f - pow(centerDist / g_light[lightIndex].range, 2));
        }
    }

    // specular 부분.
    //2를 곱해서 더한 이유는 리플렉션의 반대 부분이 생기기 떄문에. saturate는 -가 나오면 0으로 바꿔주는 것.
    float3 reflectionDir = normalize(viewLightDir + 2 * (saturate(dot(-viewLightDir, viewNormal)) * viewNormal));
    float3 eyeDir = normalize(viewPos); // 자기 자신의 좌표를 노멀라이즈 해줘서 Camera -> Pos 방향으로 단위벡터를 구해주는 것.
    specularRatio = saturate(dot(-eyeDir, reflectionDir));
    specularRatio = pow(specularRatio, 2); // 이걸 하지 않으면 범위가 넓다? 조금이라도 멀리 벗어나면 빛이 안 보이는 형태로 된다?

    
    //조명 반사의 최종 값들.
    
    //반사되는 부분들을 노말벡터와 L이라는 방향벡터를 쬐어 내적을하는 부분
    // N벡터 dot L벡터 cos세타 부분.
    color.diffuse = g_light[lightIndex].color.diffuse * diffuseRatio * distanceRatio;
    
    //그 자체가 영향이다. 혹시나 범위도 있을 수 있으니.
    color.ambient = g_light[lightIndex].color.ambient * distanceRatio;
    
    // 빛을 쬐어 반사를 하는 부분을 리플렉션이라 하는데. 라이트 벡터에다 -를 해준 것과
    // 노멀 벡터를 내적하면 삼각형이 하나 생기는데. 그 부분을 뜻한다.
    // specular 이건 다시 복습이 필요.
    color.specular = g_light[lightIndex].color.specular * specularRatio * distanceRatio;

    //조명 너무어렵다;;;
    return color;
}


#endif