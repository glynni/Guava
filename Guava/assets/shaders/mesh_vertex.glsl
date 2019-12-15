#version 450 core

// Per vertex
layout(location = 0) in vec3 position_model;
layout(location = 1) in vec3 normal_model;
layout(location = 2) in vec2 uv;

// Per instance
layout(location = 3) in mat4 modelMatrix; 
layout(location = 7) in mat4 normalMatrix;

// Uniforms
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform mat4 u_modelMatrix;
uniform mat3 u_normalMatrix;

// Out
out vec4 position_world;
out vec3 normal_world;
out vec2 uv_coords;

// Main
void main()
{
	position_world = u_modelMatrix * vec4(position_model, 1.0f);
	normal_world = normalize(u_normalMatrix * normal_model);
	uv_coords = uv;
	gl_Position = u_projectionMatrix * u_viewMatrix * position_world;
}