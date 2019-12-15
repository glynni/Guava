#include "pch.h"
#include "glTexture.h"

namespace Guava::OpenGL
{
	struct GLinternalFormat
	{
		GLenum format;
		GLenum type;
	};

	static const GLenum GetGLenum(const TextureFilterMode tfm);
	static const GLenum GetGLenum(const TextureWrappingMode twm);
	static const GLinternalFormat GetGLclientFormat(const TextureCreationInfo& tci);
	static const GLenum GetGLinternalFormat(const TextureCreationInfo& tci);

	glTexture::glTexture(const std::string_view path, const TextureCreationInfo& description) : Guava::Texture(path, description), m_Texture(0)
	{
		CreateTexture();

		if (m_PixelData.size())
		{
			CreateStorage();

			SetTextureParameter(GL_TEXTURE_MIN_FILTER,	GetGLenum(m_Info.MinFiltering)); 
			SetTextureParameter(GL_TEXTURE_MAG_FILTER,	GetGLenum(m_Info.MagFiltering)); 
			SetTextureParameter(GL_TEXTURE_WRAP_S,		GetGLenum(m_Info.HorizontalWrapping)); 
			SetTextureParameter(GL_TEXTURE_WRAP_T,		GetGLenum(m_Info.VerticalWrapping));

			GLinternalFormat glif = GetGLclientFormat(m_Info);

			glTextureSubImage2D(
				m_Texture, 
				0,									// Level
				0, 0, m_Width, m_Height,			// x, y, width, height
				glif.format, 
				glif.type, 
				m_PixelData.data());
		}

		// Free memory
		m_PixelData = ByteBuffer();
	}

	glTexture::~glTexture()
	{
		glDeleteTextures(1, &m_Texture);
	}

	void glTexture::Bind()
	{
		glBindTextureUnit(0, m_Texture);
	}

	void glTexture::CreateTexture()
	{
		GLenum type;

		switch (m_Info.Type)
		{	
		case TextureType::Texture2D: type = GL_TEXTURE_2D; break;

		default: GUAVA_ASSERT(false, "Unknown texture type specified"); break;
		}

		glCreateTextures(type, 1, &m_Texture);
	}

	void glTexture::CreateStorage()
	{
		switch (m_Info.Type)
		{
		case TextureType::Texture2D:
		{
			glTextureStorage2D(m_Texture, 1, GetGLinternalFormat(m_Info), m_Width, m_Height);
			break;
		}
		default: GUAVA_ASSERT(false, "Unknown texture type specified"); break;
		}
	}

	void glTexture::SetTextureParameter(GLenum id, GLint parameter)
	{
		glTextureParameteri(m_Texture, id, parameter);
	}

	const GLenum GetGLenum(const TextureFilterMode tfm)
	{
		switch (tfm)
		{
		case Guava::TextureFilterMode::Nearest: return GL_NEAREST;
		case Guava::TextureFilterMode::Linear:	return GL_LINEAR;

		default: GUAVA_ASSERT(false, "Unknown filter mode specified"); break;
		}
	}

	const GLenum GetGLenum(const TextureWrappingMode twm)
	{
		switch (twm)
		{
		case Guava::TextureWrappingMode::EdgeClamp: return GL_CLAMP_TO_EDGE;

		default: GUAVA_ASSERT(false, "Unknown wrapping mode specified"); break;
		}
	}

	const GLinternalFormat GetGLclientFormat(const TextureCreationInfo& tci)
	{
		switch (tci.ClientFormat)
		{
		case TexturePixelFormat::RGB8: 
		{
			return {GL_RGB, GL_UNSIGNED_BYTE};
		}
		case TexturePixelFormat::RGBA8: 
		{
			return { GL_RGBA, GL_UNSIGNED_BYTE };
		}

		default: GUAVA_ASSERT(false, "Unknown pixel format specified"); break;
		}
	}

	const GLenum GetGLinternalFormat(const TextureCreationInfo& tci)
	{
		switch (tci.GPUFormat)
		{
		case TexturePixelFormat::RGB8:	return GL_RGB8;
		case TexturePixelFormat::RGBA8: return GL_RGBA8;

		default: GUAVA_ASSERT(false, "Unknown pixel format specified"); break;
		}
	}
}
