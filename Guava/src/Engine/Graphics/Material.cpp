#include "pch.h"
#include "Material.h"
#include "Texture2D.h"
#include "Engine/Core/ResourceManager.h"

namespace Guava
{
	vector<Material*> Material::LoadAll(string_view filePath, const aiScene* scene)
	{
		vector<Material*> ret;

		if (!scene) return ret;

		auto& materials = ResourceManager::GetMaterials(filePath);

		if (materials.empty())
		{
			vector<std::function<void(void)>> Tasks;
			string_view fileDir = GetFileDirectory(filePath);
			materials.reserve(scene->mNumMaterials);
			string path;

			for (unsigned int i = 0; i < scene->mNumMaterials; ++i)
			{
				Material* newMaterial = materials.emplace_back(new Material()).get();

				aiMaterial* material = scene->mMaterials[i];
				aiString stringBuffer;
				aiColor3D colorBuffer;
				float floatBuffer;

				// Ambient factor
				if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_AMBIENT, colorBuffer))
					newMaterial->AmbientMultiplier = { colorBuffer.r, colorBuffer.g, colorBuffer.b };

				// Shininess
				if (AI_SUCCESS == material->Get(AI_MATKEY_SHININESS, floatBuffer))
					newMaterial->Shininess = floatBuffer;

				// Diffuse color / factor
				if (AI_SUCCESS == material->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), stringBuffer))
				{
					path = fileDir;
					path.append(stringBuffer.C_Str());

					Tasks.emplace_back([=]() {newMaterial->Albedo = Texture2D::LoadFromFile(path); });
				}
				if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, colorBuffer))
					newMaterial->DiffuseMultiplier = { colorBuffer.r, colorBuffer.g, colorBuffer.b };

				// Normal map
				if (AI_SUCCESS == material->Get(AI_MATKEY_TEXTURE_NORMALS(0), stringBuffer))
				{
					path = fileDir;
					path.append(stringBuffer.C_Str());

					Tasks.emplace_back([=]() {newMaterial->NormalMap = Texture2D::LoadFromFile(path); });
				}

				// Specular map / factor
				if (AI_SUCCESS == material->Get(AI_MATKEY_TEXTURE_SPECULAR(0), stringBuffer))
				{
					path = fileDir;
					path.append(stringBuffer.C_Str());

					Tasks.emplace_back([=]() {newMaterial->SpecularMap = Texture2D::LoadFromFile(path); });
				}
				if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_SPECULAR, colorBuffer))
					newMaterial->SpecularMultiplier = { colorBuffer.r, colorBuffer.g, colorBuffer.b };
			}

			// Load textures
			std::for_each(GUAVA_EXECUTION_POLICY, Tasks.begin(), Tasks.end(), [](auto& t) {t(); });
		}

		// Generate return
		ret.resize(materials.size());
		std::transform(GUAVA_EXECUTION_POLICY, materials.begin(), materials.end(), ret.begin(), [](auto& u_ptr) {return u_ptr.get(); });

		return ret;
	}

	Material::Material() :
		// Ambient
		AmbientMultiplier(vec3(1.0f)),	// K_a

		// Diffuse
		Albedo(nullptr),
		DiffuseMultiplier(vec3(1.0f)),	// K_d

		// Specular
		SpecularMap(nullptr),
		SpecularMultiplier(vec3(1.0f)),	// K_s
		SpecularStrength(1.0f),			// ???
		Shininess(1.0f),				// Exponent in specular eq

		// Normal map
		NormalMap(nullptr)
	{
	}
}