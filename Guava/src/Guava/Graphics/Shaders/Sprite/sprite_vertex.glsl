#version 450 core

// Per Vertex
layout(location = 0) in vec3 position;

// Per Instance
layout(location = 1) in vec4 tBoundaries;
layout(location = 2) in vec4 color;
layout(location = 3) in mat4 modelMatrix;

// Uniforms
uniform mat4 projectionMatrix;

// Out
out vec4 out_Color;
out vec2 out_TexCoords;

// Main
void main()
{
	switch (gl_VertexID)
	{
		case 0:	out_TexCoords = tBoundaries.xz; break;
		case 1:	out_TexCoords = tBoundaries.xw; break;
		case 2:	out_TexCoords = tBoundaries.yw; break;
		case 3:	out_TexCoords = tBoundaries.yz; break;

		default: break;
	}

	out_Color = color;
	gl_Position = projectionMatrix * modelMatrix * vec4(position, 1.0f);
}