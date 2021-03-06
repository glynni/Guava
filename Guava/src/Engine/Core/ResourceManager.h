#pragma once
namespace Guava
{
	class ResourceManager
	{
		friend class Texture2D;
		friend class Shader;
		friend class Model;
		friend class Material;

	public:

		static void Create();
		static void Destroy();

		static Texture2D* GetTexture(const string_view path);
		static Shader* GetShader(const string_view path);
		static Model* GetModel(const string_view path);
		static vector<scope<Material>>& GetMaterials(const string_view path);

	private:

		static void RegisterTexture(Texture2D* ptr, const string_view path = "");
		static void RegisterShader(Shader* ptr, const string_view name);
		static void RegisterModel(Model* ptr, const string_view path = "");

		// Storage of resources
		template<typename T>
		using Storage = u_map<string, scope<T>>;

		template<typename T>
		using Storage_Nameless = vector<scope<T>>;

		mutex Mutex;

		Storage<Texture2D>	Textures;
		Storage<Shader>		Shaders;
		Storage<Model>		Models;

		Storage_Nameless<Texture2D>	Nameless_Textures;
		Storage_Nameless<Shader>	Nameless_Shaders;
		Storage_Nameless<Model>		Nameless_Models;

		u_map<string, vector<scope<Material>>> Materials;
	};
}

