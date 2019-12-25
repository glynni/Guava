struct PointLight
{
	float	intensity;
	vec3 	position;
	vec3 	color;
};

uniform PointLight u_lights[10];
uniform int u_numLights;

uniform vec3 u_ambientLight;

