#version 330

out vec4 colour;

uniform vec3 Color;

void main()  
{
	colour = vec4(Color, 1.0f);
}
