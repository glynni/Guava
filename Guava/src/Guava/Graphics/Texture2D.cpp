#include "pch.h"
#include "stb_image.h"
#include "Texture2D.h"
#include "Guava/Core/ResourceManager.h"
#include "Guava/Graphics/Renderer.h"

namespace Guava
{
	Texture2D* Texture2D::LoadFromFile(const string_view path, const Texture2DCreateInfo& info)
	{
		Texture2D* i = ResourceManager::GetTexture(path);

		if (i) return i;

		i = Renderer::CreateTexture(info);

		if (!i->LoadFile(path))
		{
			delete i;
			return nullptr;
		}

		ResourceManager::RegisterTexture(i, path);

		return i;
	}
	Texture2D* Texture2D::LoadFromData(const size_t width, const size_t height, const vector<Byte>& data, const Texture2DCreateInfo& info)
	{
		if (data.empty()) return nullptr;
		
		auto size = data.size();

		// size = width * height * (bytes/pixel)
		const auto numPixels = width * height;

		// dimensions don't add up...
		if ((size % numPixels) != 0) return nullptr;

		const auto bytesPP = size / numPixels;
		TexturePixelFormat pf;

		switch ((TexturePixelFormat)bytesPP)
		{
		case TexturePixelFormat::RGB8: pf = TexturePixelFormat::RGB8; break;
		case TexturePixelFormat::RGBA8: pf = TexturePixelFormat::RGBA8; break;
		default: return nullptr; break;
		}

		Texture2D* i = Renderer::CreateTexture(info);

		i->m_PixelData = data;
		i->m_Info.ClientFormat = pf;
		i->m_Width = width;
		i->m_Height = height;

		ResourceManager::RegisterTexture(i);

		return i;
	}
	const unsigned int Texture2D::GetWidth() const
	{
		return m_Width;
	}

	const unsigned int Texture2D::GetHeight() const
	{
		return m_Height;
	}

	const vector<Byte>& Texture2D::GetPixelData() const
	{
		return m_PixelData;
	}

	void Texture2D::FreeData()
	{
		m_PixelData = vector<Byte>();
	}

	Texture2D::Texture2D(const Texture2DCreateInfo& info) : m_Info(info), m_Width(0), m_Height(0)
	{
	}

	bool Texture2D::LoadFile(const string_view path)
	{
		stbi_set_flip_vertically_on_load(1);

		// Load pixel data
		int width, height, channels;
		stbi_uc* data = stbi_load(path.data(), &width, &height, &channels, 0);

		if (!data)
		{
			GUAVA_ERROR("Failed to load image file: {0}", path.data());
			return false;
		}

		m_Width = width;
		m_Height = height;

		// Put data into buffer
		const size_t size = m_Width * m_Height * (size_t)channels * sizeof(unsigned char);
		m_PixelData = vector<Byte>(data, data + size);
		stbi_image_free(data);

		switch (channels)
		{
		case 3: m_Info.ClientFormat = TexturePixelFormat::RGB8; break;
		case 4: m_Info.ClientFormat = TexturePixelFormat::RGBA8; break;
		default: GUAVA_ASSERT(false, "Image file has unknown pixelformat: {0}", path.data()); break;
		}

		return true;
	}
}
