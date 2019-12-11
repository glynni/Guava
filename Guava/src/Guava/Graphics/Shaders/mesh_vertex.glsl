#version 450 core

// Per Vertex
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

// Uniforms
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ModelMatrix;

// Out
out vec4 VS_Position_World;
out vec4 VS_Normal_World;

// Main
void main()
{
	VS_Position_World = u_ModelMatrix * vec4(position, 1.0f);
	VS_Normal_World = u_ModelMatrix * vec4(normal, 0.0f);

	gl_Position = u_ProjectionMatrix * u_ViewMatrix * VS_Position_World;
}