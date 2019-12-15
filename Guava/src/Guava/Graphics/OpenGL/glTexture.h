#pragma once
#include "../Texture.h"

namespace Guava::OpenGL
{
	class glTexture : public Guava::Texture
	{
	public:

		glTexture(const StringView path, const TextureCreationInfo& description);
		~glTexture();

		void Bind() override;

	private:

		GLuint m_Texture;

		void CreateTexture();
		void CreateStorage();
		void SetTextureParameter(GLenum id, GLint parameter);
	};
}