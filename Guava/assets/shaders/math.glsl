mat3 TBN(vec3 normal, vec3 tangent, vec3 bitangent, mat4 modelMatrix)
{
	vec3 T = normalize((modelMatrix * vec4(tangent,   0.0)).xyz);
	vec3 N = normalize((modelMatrix * vec4(normal,    0.0)).xyz);
	vec3 B = normalize((modelMatrix * vec4(bitangent,    0.0)).xyz);

	return mat3(T, B, N);
}

vec3 direction(vec4 from, vec4 to)
{
	return normalize(to - from).xyz;
}

vec3 direction(vec3 from, vec3 to)
{
	return normalize(to - from);
}

vec2 direction(vec2 from, vec2 to)
{
	return normalize(to - from);
}

vec3 bisector(vec3 v1, vec3 v2)
{
	return normalize(v1 + v2);
}

vec3 bisector(vec4 v1, vec4 v2)
{
	return normalize(v1 + v2).xyz;
}

vec2 bisector(vec2 v1, vec2 v2)
{
	return normalize(v1 + v2);
}
