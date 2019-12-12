#version 450 core

in vec4 out_Color;
in vec2 out_TexCoords;

out vec4 FragColor;

uniform sampler2D diffuse;

vec3 Black = vec3(0.0f, 0.0f, 0.0f);
	
void main()
{
	vec4 diffCol = texture(diffuse, out_TexCoords);

	if(diffCol.rgb != Black)
		FragColor = out_Color * diffCol;
	else
		FragColor = out_Color;
}