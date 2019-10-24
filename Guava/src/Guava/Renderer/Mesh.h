#pragma once
#include <vector>

namespace Guava
{
	struct vec2 
	{
		vec2() : x(0.0f), y(0.0f) {}
		vec2(const float _x, const float _y) :
			x(_x), y(_y) {}

		float x, y;
	};
	struct vec3
	{
		vec3() : x(0.0f), y(0.0f), z(0.0f) {}
		vec3(const float _x, const float _y, const float _z) :
			x(_x), y(_y), z(_z) {}

		float x, y, z;
	};
	struct vec4
	{
		vec4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
		vec4(const float _x, const float _y, const float _z, const float _w) :
			x(_x), y(_y), z(_z), w(_w) {}

		float x, y, z, w;
	};

	struct Vertex3D
	{
		Vertex3D() {}
		Vertex3D(const vec3& pos, const vec2& tc, const vec4& col) :
			Position(pos), TextureCoordinates(tc), Color(col) {}

		vec3 Position;
		vec2 TextureCoordinates;
		vec4 Color;
	};

	//struct aiMesh;

	class Mesh
	{
	public:

		static Mesh* Create(const std::vector<Vertex3D>& mesh_data);
		static Mesh* Create(const std::vector<Vertex3D>& mesh_data, const std::vector<unsigned int>& index_data);
		//static Mesh* Create(const aiMesh* ai_mesh);

		virtual ~Mesh() {};

		virtual void Draw() = 0;
	};

}

