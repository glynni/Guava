#include "pch.h"
#include "glTexture2D.h"

namespace Guava::OpenGL
{
	struct GLclientFormat
	{
		GLenum format;
		GLenum type;
	};

	static const GLenum GetGLenum(const TextureWrappingMode twm);
	static const GLclientFormat GetGLclientFormat(const Texture2DCreateInfo& tci);

	glTexture2D::glTexture2D(const Texture2DCreateInfo& description) : 
		Texture2D(description), 
		m_Texture(0), 
		m_Initialized(false)
	{
	}

	glTexture2D::~glTexture2D()
	{
		glDeleteTextures(1, &m_Texture);
	}

	void glTexture2D::Bind()
	{
		UpdateGPU();
		
		glBindTextureUnit((GLuint)m_Info.Type, m_Texture);
	}

	void glTexture2D::CreateStorage()
	{
		GLsizei numLevels = 1;

		if(m_Info.Type == TextureType::Diffuse)
		{
			// Calculate number of mipmaps (log2(max(width, height)) + 1)
			double res = max(m_Width, m_Height);
			numLevels = log2(res) + 1;
		}

		glTextureStorage2D(m_Texture, numLevels, GL_RGBA8, m_Width, m_Height);
	}

	void glTexture2D::SetTextureParameter(GLenum id, GLint parameter)
	{
		glTextureParameteri(m_Texture, id, parameter);
	}

	void glTexture2D::UpdateGPU()
	{
		if (!m_Initialized)
		{
			glDeleteTextures(1, &m_Texture);
			glCreateTextures(GL_TEXTURE_2D, 1, &m_Texture);
			CreateStorage();

			GLclientFormat cf = GetGLclientFormat(m_Info);

			glTextureSubImage2D(
				m_Texture,
				0, // Level
				0, 0, m_Width, m_Height, // x, y, width, height
				cf.format,
				cf.type,
				m_PixelData.data());

			// Mipmapping and anisotropic filtering only for diffuse textures
			if (m_Info.Type == TextureType::Diffuse)
			{
				glGenerateTextureMipmap(m_Texture);

				// Check availability of extension
				if (GLAD_GL_ARB_texture_filter_anisotropic == 1)
					SetTextureParameter(GL_TEXTURE_MAX_ANISOTROPY, 4.0f);

				SetTextureParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			}
			else
				SetTextureParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			SetTextureParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			SetTextureParameter(GL_TEXTURE_WRAP_S, GetGLenum(m_Info.HorizontalWrapping));
			SetTextureParameter(GL_TEXTURE_WRAP_T, GetGLenum(m_Info.VerticalWrapping));

			FreeData();
			m_Initialized = true;
		}
	}

	const GLenum GetGLenum(const TextureWrappingMode twm)
	{
		switch (twm)
		{
		case Guava::TextureWrappingMode::EdgeClamp: return GL_CLAMP_TO_EDGE;
		case Guava::TextureWrappingMode::Repeat: return GL_REPEAT;

		default: GUAVA_ASSERT(false, "Unknown wrapping mode specified"); break;
		}
	}

	const GLclientFormat GetGLclientFormat(const Texture2DCreateInfo& tci)
	{
		switch (tci.ClientFormat)
		{
		case TexturePixelFormat::RGB8: return { GL_RGB, GL_UNSIGNED_BYTE };
		case TexturePixelFormat::RGBA8:return { GL_RGBA, GL_UNSIGNED_BYTE };

		default: GUAVA_ASSERT(false, "Unknown pixel format specified"); break;
		}
	}
}
