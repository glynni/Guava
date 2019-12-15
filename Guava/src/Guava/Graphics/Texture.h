#pragma once

namespace Guava
{
	struct PixelRGB8
	{
		uint8_t r, g, b;
	};
	struct PixelRGBA8
	{
		uint8_t r, g, b, a;
	};

	typedef std::vector<unsigned char>	ByteBuffer;
	typedef std::vector<PixelRGB8>		BufferRGB8;
	typedef std::vector<PixelRGBA8>		BufferRGBA8;

	enum class TextureType
	{
		Texture2D
	};
	enum class TextureFilterMode
	{
		Nearest,
		Linear
	};
	enum class TextureWrappingMode
	{
		EdgeClamp
	};
	enum class TexturePixelFormat
	{
		RGB8,
		RGBA8
	};
	
	struct TextureCreationInfo
	{
		TextureType Type = TextureType::Texture2D;

		TextureFilterMode MinFiltering = TextureFilterMode::Linear;
		TextureFilterMode MagFiltering = TextureFilterMode::Linear;

		TextureWrappingMode HorizontalWrapping =	TextureWrappingMode::EdgeClamp;
		TextureWrappingMode VerticalWrapping =		TextureWrappingMode::EdgeClamp;

		TexturePixelFormat ClientFormat =	TexturePixelFormat::RGB8;
		TexturePixelFormat GPUFormat =		TexturePixelFormat::RGBA8;

		bool FlipVertically = true;
	};

	class Texture
	{
	public:

		virtual ~Texture() = default;

		virtual void Bind() = 0;

		static Texture* Create(const std::string_view filePath, const TextureCreationInfo& desc = TextureCreationInfo());

	protected:

		Texture(const std::string_view filePath, const TextureCreationInfo& desc);

		ByteBuffer			m_PixelData;
		TextureCreationInfo	m_Info;
		unsigned int		m_Width;
		unsigned int		m_Height;
	};

	class TextureBoundaries
	{
	public:

		TextureBoundaries(const float left = 0.0f, const float right = 1.0f, const float bottom = 0.0f, const float top = 1.0f);

		const TextureBoundaries& GetTextureBoundaries() const;

		void SetTextureBoundaries(const float left, const float right, const float bottom, const float top);

		void SetLeft(const float left);
		void SetRight(const float right);
		void SetBottom(const float bottom);
		void SetTop(const float top);

	private:

		float m_Left, m_Right, m_Bottom, m_Top;
	};
}
