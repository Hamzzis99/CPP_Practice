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
        // Directional L�� ������ִ� ��.
        viewLightDir = normalize(mul(float4(g_light[lightIndex].direction.xyz, 0.f), g_matView).xyz);
        //saturate ������ ������ ������ 0���� ������ִ� ��. ������ �ϱ� ���� ������� ��.
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));
    }
    else if (g_light[lightIndex].lightType == 1)
    {
        // Point Light 
        // viewLightPos�� ������ ���� �ƴ��� ����. �ش� ��ü�� ������ ��ġ�� ���ϴ� ��.
        float3 viewLightPos = mul(float4(g_light[lightIndex].position.xyz, 1.f), g_matView).xyz;
        viewLightDir = normalize(viewPos - viewLightPos);
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));

        float dist = distance(viewPos, viewLightPos);
        if (g_light[lightIndex].range == 0.f) // range�� 0�� �Ǹ� ���� ����.
            distanceRatio = 0.f; // ����ó��.
        else
            distanceRatio = saturate(1.f - pow(dist / g_light[lightIndex].range, 2)); // ���� ���� ����ϰ� ����� ��. 1���� Ŀ���� saturate�� 0���� �ٲ���
    }
    else
    {
        // Spot Light
        float3 viewLightPos = mul(float4(g_light[lightIndex].position.xyz, 1.f), g_matView).xyz; // ������ ���� ��ġ
        viewLightDir = normalize(viewPos - viewLightPos); // �������� �����
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));

        if (g_light[lightIndex].range == 0.f)
            distanceRatio = 0.f; // ����üũ
        else
        {
            float halfAngle = g_light[lightIndex].angle / 2; // �þ߰� ���ϱ�.

            float3 viewLightVec = viewPos - viewLightPos; // �Ϲ������� ũ�Ⱑ ������ ���� A����
            float3 viewCenterLightDir = normalize(mul(float4(g_light[lightIndex].direction.xyz, 0.f), g_matView).xyz); // ���� ���� L����

            //���� �����Ͽ� ������ ���ư��� �Ÿ��� ���ϴ� ��.
            float centerDist = dot(viewLightVec, viewCenterLightDir);
            distanceRatio = saturate(1.f - centerDist / g_light[lightIndex].range);

            float lightAngle = acos(dot(normalize(viewLightVec), viewCenterLightDir)); // ���� ���ذͿ� ��ũ�ڻ���.

            if (centerDist < 0.f || centerDist > g_light[lightIndex].range) // �ִ� �Ÿ��� �������
                distanceRatio = 0.f;
            else if (lightAngle > halfAngle) // �ִ� �þ߰��� �������
                distanceRatio = 0.f; //����� 0����.
            else // �Ÿ��� ���� ������ ���⸦ ����
                distanceRatio = saturate(1.f - pow(centerDist / g_light[lightIndex].range, 2));
        }
    }

    // specular �κ�.
    //2�� ���ؼ� ���� ������ ���÷����� �ݴ� �κ��� ����� ������. saturate�� -�� ������ 0���� �ٲ��ִ� ��.
    float3 reflectionDir = normalize(viewLightDir + 2 * (saturate(dot(-viewLightDir, viewNormal)) * viewNormal));
    float3 eyeDir = normalize(viewPos); // �ڱ� �ڽ��� ��ǥ�� ��ֶ����� ���༭ Camera -> Pos �������� �������͸� �����ִ� ��.
    specularRatio = saturate(dot(-eyeDir, reflectionDir));
    specularRatio = pow(specularRatio, 2); // �̰� ���� ������ ������ �д�? �����̶� �ָ� ����� ���� �� ���̴� ���·� �ȴ�?

    
    //���� �ݻ��� ���� ����.
    
    //�ݻ�Ǵ� �κе��� �븻���Ϳ� L�̶�� ���⺤�͸� �ؾ� �������ϴ� �κ�
    // N���� dot L���� cos��Ÿ �κ�.
    color.diffuse = g_light[lightIndex].color.diffuse * diffuseRatio * distanceRatio;
    
    //�� ��ü�� �����̴�. Ȥ�ó� ������ ���� �� ������.
    color.ambient = g_light[lightIndex].color.ambient * distanceRatio;
    
    // ���� �ؾ� �ݻ縦 �ϴ� �κ��� ���÷����̶� �ϴµ�. ����Ʈ ���Ϳ��� -�� ���� �Ͱ�
    // ��� ���͸� �����ϸ� �ﰢ���� �ϳ� ����µ�. �� �κ��� ���Ѵ�.
    // specular �̰� �ٽ� ������ �ʿ�.
    color.specular = g_light[lightIndex].color.specular * specularRatio * distanceRatio;

    //���� �ʹ���ƴ�;;;
    return color;
}


#endif