#version 330 core

uniform vec4 color1;
uniform vec4 color2;
uniform vec4 color3;

in vec2 position;

out vec4 fragColor;

void main ()
{
	float positionY  = position.y + 0.5;
	vec4 color;
    
	if (positionY < 0.33)  color = color3; 
    else if (positionY < 0.66) color = color2; 
    else color = color1; 
    
    fragColor = color;
}
