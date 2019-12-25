/*Out*******************************************************************************/
out vec4 fragColor;

/*Uniforms**************************************************************************/

// Material
uniform vec3		u_ka;
uniform vec3		u_kd;
uniform vec3		u_ks;
uniform float		u_specularStr;
uniform float		u_shininess;		
uniform sampler2D 	u_diffuse;
uniform sampler2D 	u_specular;
uniform sampler2D 	u_normalMap;

/*Blinn-Phong********************************************************************/
vec3 bp_ambient(vec3 ambientLightColor, vec3 k_ambient)
{
	return k_ambient * ambientLightColor;
}

vec3 bp_diffuse(vec3 lightColor, vec3 k_diff, vec3 normal, vec3 lightDir)
{
	return lightColor * k_diff * max(0.0f, dot(normal, lightDir));
}

vec3 bp_specular(vec3 lightColor, vec3 kspec, vec3 normal, vec3 lightDir, vec3 viewDir, float shine)
{
	return lightColor * kspec * pow(max(0, dot(normal, bisector(lightDir, viewDir))), shine);
}

void blinn_phong()
{
	vec3 bp = vec3(0.0f);

	if(u_numLights > 0)
	{
		vec3 viewDir = direction(fs.position, fs.eyePos);
		vec3 ks =  u_ks * texture(u_specular, fs.uv).rgb;
		vec3 normal = GetNormalFromMap(texture(u_normalMap, fs.uv).rgb);
		
		for(int i = 0; i < u_numLights; ++i)
		{
			if(u_lights[i].intensity > 0.0f)
			{
				// calculate light direction
				vec3 lightDir = direction(fs.position, fs.lightPos[i]);
				
				// calculate final light color
				vec3 lightIntensity = u_lights[i].intensity * u_lights[i].color;

				// add diffuse lighting
				bp += bp_diffuse(lightIntensity, u_kd, normal, lightDir);

				// add specular highlight
				bp += u_specularStr * bp_specular(lightIntensity, ks, normal, lightDir, viewDir, u_shininess);
			}
		}
	}

	// add ambient component
	bp += bp_ambient(u_ambientLight, u_ka);

	// sample diffuse texture
	fragColor = texture(u_diffuse, fs.uv) * vec4(bp, 1.0f);
}

/*Corrections********************************************************************/
void correct_gamma()
{
	fragColor.rgb = pow(fragColor.rgb, vec3(1.0/2.2f));
}

/*Main**************************************************************************/
void main()
{
	blinn_phong();
	correct_gamma();
}

