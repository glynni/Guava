#version 450 core

// Per vertex
layout(location = 0) in vec3 position_model;
layout(location = 1) in vec3 normal_model;

// Per instance
layout(location = 2) in mat4 modelMatrix; // locations 2, 3, 4, 5

// Uniforms
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform mat4 u_modelMatrix;

// Out
out vec4 position_world;
out vec4 normal_world;

// Main
void main()
{
	position_world = u_modelMatrix * vec4(position_model, 1.0f);
	normal_world = u_modelMatrix * vec4(normal_model, 0.0f);

	gl_Position = u_projectionMatrix * u_viewMatrix * position_world;
}