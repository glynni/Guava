#version 450 core

// In
in vec4 VS_Normal_World;
in vec4 VS_Position_World;

// Out
out vec4 FragColor;

// Surface
vec4 SurfaceColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

// Light
float LightIntensity = 1.0f;
vec4  LightPos = vec4(0.0f, 0.0f, 0.0f, 1.0f);
vec4  LightColor = vec4(0.5f, 0.5f, 1.0f, 1.0f);

// Eye
uniform vec4 u_EyePos;

/* Vector math ************************************************************************/
vec4 Direction(vec4 from, vec4 to)
{
	return normalize(to - from);
}
vec4 Bisector(vec4 v1, vec4 v2)
{
	return v1 + v2;
}

/* Shader models ************************************************************************

	Don't forget:
	- Constant Factors
	- Intensity

	LightDir:	surface ---> light
	ViewDir:	surface ---> eye
*/

// Lambertian = max(0, dot(normal, lightDir))
float Lambertian(vec4 n, vec4 l)
{
	return max(0.0f, dot(n, l));
}

// BlinnPhong = Lambertian + max(0, dot(normal, bisector(viewDir, lightDir)))^hackValue
float BlinnPhong(vec4 n, vec4 l, vec4 viewDir, float p)
{
	vec4 h = normalize(Bisector(l, viewDir));
	return Lambertian(n, l) + pow(max(0, dot(n, h)), p);
}

/* main ************************************************************************/
void main()
{
	vec4 ViewDir = Direction(VS_Position_World, u_EyePos);
	vec4 LightDir = Direction(VS_Position_World, LightPos);
	
	//FragColor = SurfaceColor * LightColor * Lambertian(LightIntensity, VS_Normal_World, LightDir);
	FragColor = SurfaceColor * LightColor * LightIntensity * BlinnPhong(VS_Normal_World, LightDir, ViewDir, 100.0f);
}