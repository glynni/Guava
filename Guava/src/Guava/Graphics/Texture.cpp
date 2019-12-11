#include "pch.h"
#include "Texture.h"
#include "stb_image.h"
#include "Renderer.h"

namespace Guava
{
	const std::vector<unsigned char>& Texture::GetPixelData() const
	{
		return m_PixelData;
	}

	const Texture::Description& Texture::GetTextureInfo() const
	{
		return m_Info;
	}

	void Texture::ReleaseMemory()
	{
		m_PixelData = std::vector<unsigned char>();
	}

	Texture* Texture::Create(const Texture::Description& description, const std::string_view filePath)
	{
		return Renderer::CreateTexture(description, filePath);
	}

	Texture::Texture(const Texture::Description& info, std::string_view path)
	{
		stbi_set_flip_vertically_on_load(1);
		int width, height, channels;
		stbi_uc* data = stbi_load(path.data(), &width, &height, &channels, 0);

		GUAVA_ASSERT(data != nullptr, "Failed to load texture file: {0}", path);

		const size_t size = (size_t)width * (size_t)height * (size_t)channels * (size_t)sizeof(unsigned char);
		m_PixelData = std::vector<unsigned char>(data, data + size);

		stbi_image_free(data);
		m_Info = info;

		m_Info.Width = width;
		m_Info.Height = height;
		m_Info.PixelFormat = static_cast<PixelFormat>(channels);
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

