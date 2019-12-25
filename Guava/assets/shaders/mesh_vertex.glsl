/*In, per vertex, modelspace************************************************/
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent;
layout(location = 3) in vec3 bitangent;
layout(location = 4) in vec2 uv;

/*In, per instance, modelspace************************************************/
layout(location = 5) in mat4 modelMatrix;
//layout(location = 6) 
//layout(location = 7) 
//layout(location = 8) 

/*Uniforms*****************************************************************/
uniform vec3 u_eyePos;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform mat4 u_modelMatrix;

/*Lights*****************************************************************/
void ProcessLights(mat3 tbn)
{
	for(int i = 0; i < u_numLights; ++i)
		vs.lightPos[i] = tbn * u_lights[i].position;
}

/*main**********************************************************************/
void main()
{
	mat3 tbn = transpose(TBN(normal, tangent, bitangent, modelMatrix));

	vs.uv = uv;
	vs.position = tbn * (modelMatrix * vec4(position, 1.0f)).xyz;
	vs.eyePos = tbn * u_eyePos;

	vs.normal = normal;
	vs.tangent = tangent;
	vs.bitangent = bitangent;

	ProcessLights(tbn);

	gl_Position = u_projectionMatrix * u_viewMatrix * modelMatrix * vec4(position, 1.0f);
}

