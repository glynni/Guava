#include "pch.h"
#include "glTexture.h"

namespace Guava::OpenGL
{
	static GLenum PixelFormat(const glTexture::PixelFormat pf)
	{
		switch (pf)
		{
		case glTexture::PixelFormat::RGB: return GL_RGB;
		case glTexture::PixelFormat::RGBA: return GL_RGBA;
		default: GUAVA_ASSERT(false, "Unknown input-format specified.");
		}
	}
	static GLenum FilterMode(const glTexture::FilterMode fm)
	{
		switch (fm)
		{
		case glTexture::FilterMode::Nearest: return GL_NEAREST;
		case glTexture::FilterMode::Linear: return GL_LINEAR;
		default: GUAVA_ASSERT(false, "Unknown filter-mode format specified.");
		}
	}
	static GLenum WrappingMode(const glTexture::WrappingMode wm)
	{
		switch (wm)
		{
		case glTexture::WrappingMode::EdgeClamp: return GL_CLAMP_TO_EDGE;

		default: GUAVA_ASSERT(false, "Unknown wrapping-mode format specified.");
		}
	}

	glTexture::Info Convert(const Guava::Texture::Description& info)
	{
		glTexture::Info glDesc;

		glDesc.MinFilter = FilterMode(info.MinFiltering);
		glDesc.MagFilter = FilterMode(info.MagFiltering);

		glDesc.WrapS = WrappingMode(info.HorizontalWrapping);
		glDesc.WrapT = WrappingMode(info.VerticalWrapping);

		glDesc.PixelFormat = PixelFormat(info.PixelFormat);

		return glDesc;
	}

	glTexture::glTexture(const Guava::Texture::Description& info, const std::string_view path) : Guava::Texture(info, path), m_Texture(0)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_Texture);

		if (m_PixelData.size())
		{
			glTextureStorage2D(m_Texture, 1, GL_RGBA8, m_Info.Width, m_Info.Height);

			glTexture::Info glInfo = Convert(m_Info);

			glTextureParameteri(m_Texture, GL_TEXTURE_MIN_FILTER, glInfo.MinFilter); 
			glTextureParameteri(m_Texture, GL_TEXTURE_MAG_FILTER, glInfo.MagFilter); 
			glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_S	, glInfo.WrapS); 
			glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_T	, glInfo.WrapT);

			glTextureSubImage2D(m_Texture, 0, 0, 0, m_Info.Width, m_Info.Height, glInfo.PixelFormat, GL_UNSIGNED_BYTE, m_PixelData.data());
		}

		ReleaseMemory();
	}

	glTexture::~glTexture()
	{
		glDeleteTextures(1, &m_Texture);
	}

	void glTexture::Bind()
	{
		glBindTextureUnit(0, m_Texture);
	}
}
