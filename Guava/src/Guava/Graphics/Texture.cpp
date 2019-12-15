#include "pch.h"
#include "Texture.h"
#include "stb_image.h"
#include "Renderer.h"
#include "Guava/Core/AssetManager.h"

namespace Guava
{
	Texture* Texture::Create(const std::string_view filePath, const TextureCreationInfo& desc)
	{
		return AssetManager::GetTexture(filePath, desc);
	}

	Texture::Texture(const std::string_view filePath, const TextureCreationInfo& desc)
	{
		m_Info = desc;

		stbi_set_flip_vertically_on_load(m_Info.FlipVertically ? 1 : 0);

		// Load pixel data
		int width, height, channels;
		stbi_uc* data = stbi_load(filePath.data(), &width, &height, &channels, 0);
		GUAVA_ASSERT(data != nullptr, "Failed to load texture file: {0}", filePath.data());
		m_Width = width;
		m_Height = height;

		// Put data into buffer
		const size_t size = (size_t)width * (size_t)height * (size_t)channels * sizeof(unsigned char);
		m_PixelData = ByteBuffer(data, data + size);

		switch (channels)
		{
			case 3: m_Info.ClientFormat = TexturePixelFormat::RGB8; break;
			case 4: m_Info.ClientFormat = TexturePixelFormat::RGBA8; break;
			default: break;
		}

		//GUAVA_CORE_TRACE(" resolution: {0}x{1}", m_Width, m_Height);
		//GUAVA_CORE_TRACE(" channels: {0}", channels);

		stbi_image_free(data);
	}

	TextureBoundaries::TextureBoundaries(const float left, const float right, const float bottom, const float top) :
		m_Left(left),
		m_Right(right),
		m_Bottom(bottom),
		m_Top(top)
	{
	}

	const TextureBoundaries& TextureBoundaries::GetTextureBoundaries() const
	{
		return *this;
	}

	void TextureBoundaries::SetTextureBoundaries(const float left, const float right, const float bottom, const float top)
	{
		m_Left = left;
		m_Right = right;
		m_Bottom = bottom;
		m_Top = top;
	}

	void TextureBoundaries::SetLeft(const float left)
	{
		m_Left = left;
	}

	void TextureBoundaries::SetRight(const float right)
	{
		m_Right = right;
	}

	void TextureBoundaries::SetBottom(const float bottom)
	{
		m_Bottom = bottom;
	}

	void TextureBoundaries::SetTop(const float top)
	{
		m_Top = top;
	}
}

