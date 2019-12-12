#pragma once
#include "Mesh.h"

namespace Guava
{
	using MeshList = std::vector<std::unique_ptr<Mesh>>;

	class Model
	{
	public:

		Model(const std::string_view filePath);
		const MeshList& GetMeshList() const;

		static Model* Create(const std::string_view filePath);

	private:

		MeshList m_Meshes;
	};
}

