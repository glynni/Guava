#pragma once

namespace Guava
{
	enum class TextureType
	{
		Diffuse,
		SpecularMap,
		NormalMap
	};
	enum class TextureWrappingMode
	{
		EdgeClamp,
		Repeat
	};
	enum class TexturePixelFormat
	{
		RGB8 = 3,
		RGBA8 = 4
	};

	struct Texture2DCreateInfo
	{
		TextureType Type = TextureType::Diffuse;

		TextureWrappingMode HorizontalWrapping =	TextureWrappingMode::Repeat;
		TextureWrappingMode VerticalWrapping =		TextureWrappingMode::Repeat;

		TexturePixelFormat ClientFormat =	TexturePixelFormat::RGB8;
	};

	class Texture2D
	{
	public:

		virtual ~Texture2D() = default;
		Texture2D() = delete;

		virtual void Bind() = 0;

		static Texture2D* LoadFromFile(const string_view path, const Texture2DCreateInfo& info = Texture2DCreateInfo());
		static Texture2D* LoadFromData(const size_t width, const size_t height, const vector<Byte>& data, const Texture2DCreateInfo& info = Texture2DCreateInfo());

		const unsigned int GetWidth() const;
		const unsigned int GetHeight() const;
		const vector<Byte>& GetPixelData() const;

	protected:

		Texture2D(const Texture2DCreateInfo& info);

		size_t			m_Width;
		size_t			m_Height;
		vector<Byte>	m_PixelData;

		Texture2DCreateInfo	m_Info;

		void FreeData();
		virtual void UpdateGPU() = 0;

	private:

		bool LoadFile(const string_view path);
	};
}
