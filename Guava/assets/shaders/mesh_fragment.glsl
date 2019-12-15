#version 450 core

// In
in vec4 position_world;
in vec3 normal_world;
in vec2 uv_coords;

// Out
out vec4 fragColor;

// Uniforms
uniform vec4 u_eyePos;
uniform sampler2D u_diffuse;

// Lights
struct PointLight
{
	float	intensity;
	vec4 	position_world;
	vec4 	color;
};
uniform PointLight u_lights[100];
uniform int u_numLights;

/*Vector math**************************************************************************/
vec3 direction(vec4 from, vec4 to);
vec3 bisector(vec3 v1, vec3 v2);
vec3 bisector(vec4 v1, vec4 v2);
/*Shading models***********************************************************************/
float lambertian(vec3 n, vec3 l);
vec4 blinn_phong(PointLight light, vec3 normal, vec4 fragPos, vec4 eyePos, float shine);
/*Corrections**************************************************************************/
vec4 correct_gamma(vec4 fColor);
/**************************************************************************************/

void main()
{
	//vec4 surfaceColor = vec4(uv_coords, 0.0f, 1.0f);
	vec4 surfaceColor = texture(u_diffuse, uv_coords);
	vec4 ambient = 1.0f * vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vec4 diffuse_specular = vec4(0.0f, 0.0f, 0.0f, 1.0f);

	for(int i = 0; i < u_numLights; ++i)
		;//diffuse_specular += blinn_phong(u_lights[i], normal_world, position_world, u_eyePos, 10.f);

	// Gamma correction, applied at the very end / after all passes are done
	fragColor = correct_gamma(surfaceColor * (ambient + diffuse_specular));
}

/* Vector math ************************************************************************/
vec3 direction(vec4 from, vec4 to)
{
	return normalize(to - from).xyz;
}

vec3 bisector(vec3 v1, vec3 v2)
{
	return normalize(v1 + v2);
}

vec3 bisector(vec4 v1, vec4 v2)
{
	return normalize(v1 + v2).xyz;
}

/* Shading models *********************************************************************/
float lambertian(vec3 n, vec3 l)
{
	return max(0.0f, dot(n, l));
}

vec4 blinn_phong(PointLight light, vec3 normal, vec4 fragPos, vec4 eyePos, float shine)
{
	vec3 lightDir = direction(fragPos, light.position_world);
	vec3 viewDir = direction(fragPos, eyePos);
	float diffuse_specular = lambertian(normal, lightDir) + pow(max(0, dot(normal, bisector(lightDir, viewDir))), shine);

	return light.intensity * light.color * diffuse_specular;
}

/*Corrections**************************************************************************/
vec4 correct_gamma(vec4 fColor)
{
	fColor.rgb = pow(fColor.rgb, vec3(1.0/2.2f));
	return fColor;
}