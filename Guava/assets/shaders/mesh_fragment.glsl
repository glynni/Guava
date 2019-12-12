#version 450 core

// In
in vec4 position_world;
in vec4 normal_world;

// Out
out vec4 fragColor;

// Eye
uniform vec4 u_eyePos;

// Lights
struct PointLight
{
	float	intensity;
	vec4 	position_world;
	vec4 	color;
};

uniform PointLight u_light;

/* Vector math ************************************************************************/
vec4 direction(vec4 from, vec4 to)
{
	return normalize(to - from);
}
vec4 bisector(vec4 v1, vec4 v2)
{
	return normalize(v1 + v2);
}

/* Shader models ************************************************************************

	Don't forget:
	- Intensity
	- Light Color ?

	lightDir_world:	surface ---> light
	viewDir_world:	surface ---> eye
*/

// lambertian = max(0, dot(normal, lightDir))
float lambertian(vec4 n, vec4 l)
{
	return max(0.0f, dot(n, l));
}

// blinn_phong = lambertian + max(0, dot(normal, bisector(viewDir, lightDir)))^shininess
float blinn_phong(vec4 n, vec4 l, vec4 viewDir, float s)
{
	return lambertian(n, l) + pow(max(0, dot(n, bisector(l, viewDir))), s);
}

// ligthing model
vec4 PointLightOutput(PointLight light, vec4 pos, vec4 n, vec4 viewDir, float s)
{
	vec4 lightDir = direction(pos, light.position_world);

	return light.color * light.intensity * blinn_phong(n, lightDir, viewDir, s);
}

/* main ************************************************************************/
void main()
{
	// Surface
	vec4 surfaceColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Red light
	PointLight red;
	red.intensity = 		0.6f;
	red.position_world = 	vec4(24.0f, 0.0f, 12.0f, 1.0f);
	red.color = 			vec4(1.0f, 0.3f, 0.3f, 1.0f);

	// Green light
	PointLight green;
	green.intensity = 		0.6f;
	green.position_world = 	vec4(24.0f, -12.0f, 12.0f, 1.0f);
	green.color = 			vec4(0.3f, 1.0f, 0.3f, 1.0f);

	// Blue light
	PointLight blue;
	blue.intensity = 		0.6f;
	blue.position_world = 	vec4(24.0f, -24.0f, 12.0f, 1.0f);
	blue.color = 			vec4(0.3f, 0.3f, 1.0f, 1.0f);

	vec4 viewDir_world = direction(position_world, u_eyePos);
	
	//fragColor = surfaceColor * lightColor * lambertian(lightIntensity, VS_Normal_World, lightDir_world);
	fragColor  = surfaceColor * PointLightOutput(red, position_world, normal_world, viewDir_world, 10.0f);
	fragColor += surfaceColor * PointLightOutput(blue, position_world, normal_world, viewDir_world, 10.0f);
	fragColor += surfaceColor * PointLightOutput(green, position_world, normal_world, viewDir_world, 10.0f);
}