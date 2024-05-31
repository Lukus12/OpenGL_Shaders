#version 330 core

uniform sampler2D texture_0;

in vec2 texCoord;

out vec4 outputColor;

void main(void)
{
    vec4 texColor = texture(texture_0, texCoord);
	outputColor.r= 0.523 * texColor.r + 0.412 * texColor.g + 0.321 * texColor.b; 
	outputColor.g = 0.579 * texColor.r + 0.686 * texColor.g + 0.863 * texColor.b; 
	outputColor.b = 0.542 * texColor.r + 0.123 * texColor.g + 0.192 * texColor.b; 
	outputColor.a = 1.0;
}