/*In************************************************/

// Per vertex
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent;
layout(location = 3) in vec3 bitangent;
layout(location = 4) in vec2 uv;

// Per instance
layout(location = 5) in mat4 modelMatrix; // 6, 7, 8

/*Out*******************************************************************************/
out SHARED
{
	vec2 uv;
	vec3 position;		// Tangent space
	vec3 eyePos;		// Tangent space
	vec3 lightDir;		// Tangent space

} vs;

/*Uniforms*****************************************************************/
uniform vec3 u_eyePos;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

/*main**********************************************************************/
void main()
{
	mat3 tbn = transpose(TBN(normal, tangent, bitangent, modelMatrix));

	vs.uv = uv;
	vs.position = 	tbn * (modelMatrix * vec4(position, 1.0f)).xyz;
	vs.eyePos = 	tbn * u_eyePos;
	vs.lightDir = 	tbn * direction(vec3(0.0f), vec3(1.0f));

	gl_Position = u_projectionMatrix * u_viewMatrix * modelMatrix * vec4(position, 1.0f);
}

