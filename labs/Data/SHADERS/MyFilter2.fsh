#version 330 core

uniform sampler2D texture_0;

in vec2 texCoord;

out vec4 outputColor;

void main()
{
    vec2 offset = 1.0 / textureSize(texture_0, 0); // Вычисляем смещение для одного пикселя
    vec4 sum = vec4(0.0); // Начальная сумма цветов всех пикселей

    sum += texture(texture_0, texCoord + vec2(-1, -1) * offset);
    sum += texture(texture_0, texCoord + vec2(0, -1) * offset);
    sum += texture(texture_0, texCoord + vec2(1, -1) * offset);
    sum += texture(texture_0, texCoord + vec2(-1, 0) * offset);
    sum += texture(texture_0, texCoord + vec2(0, 0) * offset);
    sum += texture(texture_0, texCoord + vec2(1, 0) * offset);
    sum += texture(texture_0, texCoord + vec2(-1, 1) * offset);
    sum += texture(texture_0, texCoord + vec2(0, 1) * offset);
    sum += texture(texture_0, texCoord + vec2(1, 1) * offset);

    outputColor = sum / 9.0; // Усредняем цвета 9 соседних пикселей
}