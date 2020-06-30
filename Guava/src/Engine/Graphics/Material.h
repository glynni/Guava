#pragma once
namespace Guava
{
	class Texture2D;

	class Material
	{
	public:

		static vector<Material*> LoadAll(string_view path, const aiScene* scene);

		// Ambient
		vec3 AmbientMultiplier;		// K_a

		// Diffuse
		Texture2D* Albedo;
		vec3 DiffuseMultiplier;		// K_d

		// Specular map
		Texture2D* SpecularMap;
		vec3 SpecularMultiplier;	// K_s
		float SpecularStrength;		// ???
		float Shininess;			// Exponent in specular eq

		// Normal map
		Texture2D* NormalMap;

		Material();
	};
}

