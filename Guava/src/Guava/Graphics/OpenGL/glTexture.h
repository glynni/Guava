#pragma once
#include "../Texture.h"

namespace Guava::OpenGL
{
	class glTexture : public Guava::Texture
	{
	public:

		struct Info
		{
			GLenum MinFilter = GL_LINEAR;
			GLenum MagFilter = GL_LINEAR;
			GLenum WrapS = GL_CLAMP_TO_EDGE;
			GLenum WrapT = GL_CLAMP_TO_EDGE;
			GLenum PixelFormat = GL_RGB;
		};

		glTexture(const Guava::Texture::Description& description, const std::string_view path);
		~glTexture();

		void Bind() override;

	private:

		GLuint m_Texture;
	};
}