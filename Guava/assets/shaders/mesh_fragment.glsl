/*In*******************************************************************************/
in SHARED
{
	vec2 uv;
	vec3 position;		// Tangent space
	vec3 eyePos;		// Tangent space
	vec3 lightDir;		// Tangent space

} fs;

/*Out*******************************************************************************/
out vec4 fragColor;

/*Uniforms**************************************************************************/
uniform vec3		u_ka;
uniform vec3		u_kd;
uniform vec3		u_ks;
uniform vec3 		u_ambientLight;
uniform float		u_specularStrength;
uniform float		u_shininess;		
uniform sampler2D 	u_samplerAlbedo;
uniform sampler2D 	u_samplerSpecular;
uniform sampler2D 	u_samplerNormal;

/*Main**************************************************************************/
void main()
{
	vec4 diffuseSample = texture(u_samplerAlbedo, fs.uv);
	vec3 specularSample = texture(u_samplerSpecular, fs.uv).rgb;
	vec3 normalSample = texture(u_samplerNormal, fs.uv).rgb;

	vec3 viewDir = direction(fs.position, fs.eyePos);
	vec3 normal = GetNormalFromMap(normalSample);
	vec3 ks =  u_specularStrength * u_ks * specularSample;

	vec3 lighting;

	// diffuse + specular, do this per light
	lighting = blinn_phong(normal, fs.lightDir, viewDir, vec3(1.0f), u_kd, ks, u_shininess);

	// add ambient component
	lighting += ambient(u_ambientLight, u_ka);

	fragColor = diffuseSample * vec4(lighting, 1.0f);
	fragColor = correct_gamma(fragColor);
}

