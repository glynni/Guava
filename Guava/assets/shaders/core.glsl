/*Simple Shading********************************************************************/
vec3 ambient(vec3 ambientLightColor, vec3 k_ambient)
{
	return k_ambient * ambientLightColor;
}

vec3 blinn_phong(vec3 normal, vec3 lightDir, vec3 viewDir, vec3 lightColor, vec3 k_diff, vec3 k_spec, float shininess)
{
	vec3 bp = vec3(0.0f);

	// add diffuse lighting
	bp += lightColor * k_diff * max(0.0f, dot(normal, lightDir));

	// add specular highlight
	bp += lightColor * k_spec * pow(max(0.0f, dot(normal, bisector(lightDir, viewDir))), shininess);
	
	return bp;
}

/*Gamme correction********************************************************************/
vec4 correct_gamma(vec4 color)
{
	color.rgb = pow(color.rgb, vec3(1.0/2.2f));
	return color;
}

/*Normal mapping********************************************************************/
vec3 GetNormalFromMap(vec3 normalMapSample)
{
	return normalize(normalMapSample * 2.0 - 1.0);
}

