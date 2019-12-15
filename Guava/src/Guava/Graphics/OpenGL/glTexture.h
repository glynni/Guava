#pragma once
#include "../Texture.h"

namespace Guava::OpenGL
{
	class glTexture : public Guava::Texture
	{
	public:

		glTexture(const std::string_view path, const TextureCreationInfo& description);
		~glTexture();

		void Bind() override;

	private:

		GLuint m_Texture;

		void CreateTexture();
		void CreateStorage();
		void SetTextureParameter(GLenum id, GLint parameter);
	};
}