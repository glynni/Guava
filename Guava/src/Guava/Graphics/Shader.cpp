#include "pch.h"
#include "Shader.h"
#include "Guava/Core/ResourceManager.h"
#include "Guava/Graphics/Renderer.h"
#include "Guava/Graphics/Material.h"
#include "Guava/Graphics/Texture2D.h"

namespace Guava
{
	const static string ShaderLocation("assets/shaders/");
	static string ShaderIncludes;
	static string SharedBlock;
	static bool Initialized = false;

	static void Init()
	{
		if (!Initialized)
		{
			TextFile Math(ShaderLocation + "math.glsl");
			TextFile Core(ShaderLocation + "core.glsl");
			TextFile Shared(ShaderLocation + "shared.glsl");

			ShaderIncludes = "#version 450 core\n";

			ShaderIncludes.append(Math.GetContent());
			ShaderIncludes.append(Core.GetContent());

			SharedBlock = Shared.GetContent();

			Initialized = true;
		}
	}

	void Shader::ApplyMaterial(Material* mat)
	{
		if (!mat || m_CurrentMaterial == mat) return;

		m_CurrentMaterial = mat;

		static bool initialized = false;

		static Texture2D* missingDiffuse;
		static Texture2D* missingSpecular;
		static Texture2D* missingNormal;

		Bind();

		if (!initialized)
		{
			SetInt("u_diffuse", (unsigned int)TextureType::Diffuse);
			SetInt("u_specular", (unsigned int)TextureType::SpecularMap);
			SetInt("u_normalMap", (unsigned int)TextureType::NormalMap);

			Texture2DCreateInfo specularInfo;
			specularInfo.Type = TextureType::SpecularMap;
			specularInfo.ClientFormat = TexturePixelFormat::RGB8;

			Texture2DCreateInfo normalInfo;
			normalInfo.Type = TextureType::NormalMap;
			normalInfo.ClientFormat = TexturePixelFormat::RGB8;

			missingDiffuse = Texture2D::LoadFromFile("assets/textures/missing.png");
			missingSpecular = Texture2D::LoadFromData(1, 1, { 0, 0, 0 }, specularInfo);
			missingNormal = Texture2D::LoadFromData(1, 1, { 0, 0, 255 }, normalInfo);

			initialized = true;
		}

		SetVec3("u_ka", mat->AmbientMultiplier);
		SetVec3("u_kd", mat->DiffuseMultiplier);
		SetVec3("u_ks", mat->SpecularMultiplier);

		SetFloat("u_specularStr", mat->SpecularStrength);
		SetFloat("u_shininess", mat->Shininess);

		if (mat->Diffuse) mat->Diffuse->Bind(); else
		missingDiffuse->Bind();

		if (mat->SpecularMap) mat->SpecularMap->Bind(); else
		missingSpecular->Bind();

		if (mat->NormalMap) mat->NormalMap->Bind(); else
		missingNormal->Bind();
	}

	Shader* Shader::LoadFromFiles(const string_view vsFile, const string_view fsFile)
	{
		string key;
		key.reserve(vsFile.size() + fsFile.size() + 5);
		key.append(vsFile);
		key.append(", ");
		key.append(fsFile);

		Shader* s = ResourceManager::GetShader(key);
		if (s) return s;

		Init();

		s = Renderer::CreateShader();

		TextFile vs(ShaderLocation + vsFile.data());
		TextFile fs(ShaderLocation + fsFile.data());

		const auto vsContent = vs.GetContent();
		const auto fsContent = fs.GetContent();

		s->m_VertexCode = ShaderIncludes;
		s->m_VertexCode.append("out ");
		s->m_VertexCode.append(SharedBlock);
		s->m_VertexCode.append(" vs;\n");
		s->m_VertexCode.append(vsContent);

		s->m_FragmentCode = ShaderIncludes;
		s->m_FragmentCode.append("in ");
		s->m_FragmentCode.append(SharedBlock);
		s->m_FragmentCode.append(" fs;\n");
		s->m_FragmentCode.append(fsContent);

		ResourceManager::RegisterShader(s, key);

		return s;
	}

	Shader::Shader() : m_CurrentMaterial(nullptr)
	{
	}

	void Shader::FreeData()
	{
		m_VertexCode = string();
		m_FragmentCode = string();
	}
}

