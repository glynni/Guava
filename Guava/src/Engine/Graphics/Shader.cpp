#include "pch.h"
#include "Shader.h"
#include "Engine/Core/ResourceManager.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Material.h"
#include "Engine/Graphics/Texture2D.h"

namespace Guava
{
	const static string ShaderLocation("assets/shaders/");
	static string ShaderIncludes;
	static bool Initialized = false;

	static void Init()
	{
		if (!Initialized)
		{
			TextFile Math(ShaderLocation + "math.glsl");
			TextFile Core(ShaderLocation + "core.glsl");

			ShaderIncludes = "#version 450 core\n";

			ShaderIncludes.append(Math.GetContent());
			ShaderIncludes.append(Core.GetContent());

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
			SetInt("u_samplerAlbedo", (unsigned int)TextureSlot::Diffuse);
			SetInt("u_samplerSpecular", (unsigned int)TextureSlot::SpecularMap);
			SetInt("u_samplerNormal", (unsigned int)TextureSlot::NormalMap);

			Texture2DCreateInfo info;
			info.ClientFormat = TexturePixelFormat::RGB8;

			missingDiffuse = Texture2D::LoadFromFile("assets/textures/missing.png");
			missingSpecular = Texture2D::LoadFromData(1, 1, { 0, 0, 0 }, info);
			missingNormal = Texture2D::LoadFromData(1, 1, { 127, 127, 255 }, info); // (0.5, 0.5, 1.0) -> (0, 0, 1.0)
			
			initialized = true;
		}

		SetVec3("u_ka", mat->AmbientMultiplier);
		SetVec3("u_kd", mat->DiffuseMultiplier);
		SetVec3("u_ks", mat->SpecularMultiplier);
		
		SetFloat("u_specularStrength", mat->SpecularStrength);
		SetFloat("u_shininess", mat->Shininess);

		if (mat->Albedo) mat->Albedo->Bind(TextureSlot::Diffuse); else
		missingDiffuse->Bind(TextureSlot::Diffuse);

		if (mat->SpecularMap) mat->SpecularMap->Bind(TextureSlot::SpecularMap); else
		missingSpecular->Bind(TextureSlot::SpecularMap);

		if (mat->NormalMap) mat->NormalMap->Bind(TextureSlot::NormalMap); else
		missingNormal->Bind(TextureSlot::NormalMap);
	}

	Shader* Shader::LoadFromName(const string_view name)
	{
		Shader* s = ResourceManager::GetShader(name);
		if (s) return s;

		Init();

		s = Renderer::CreateShader();

		TextFile vs(ShaderLocation + name.data() + "_vertex.glsl");
		TextFile fs(ShaderLocation + name.data() + "_fragment.glsl");

		const auto vsContent = vs.GetContent();
		const auto fsContent = fs.GetContent();

		s->m_VertexCode = ShaderIncludes;
		s->m_VertexCode.append(vsContent);

		s->m_FragmentCode = ShaderIncludes;
		s->m_FragmentCode.append(fsContent);

		ResourceManager::RegisterShader(s, name);

		return s;
	}

	Shader::Shader() : m_CurrentMaterial(nullptr)
	{
	}

	void Shader::FreeMemory()
	{
		m_VertexCode = string();
		m_FragmentCode = string();
	}
}

