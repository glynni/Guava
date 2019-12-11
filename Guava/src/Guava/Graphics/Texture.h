#pragma once

namespace Guava
{
	class Texture
	{
	public:

		enum class FilterMode
		{
			Nearest,
			Linear
		};
		enum class WrappingMode
		{
			EdgeClamp
		};
		enum class PixelFormat
		{
			RGB = 3,
			RGBA = 4
		};
		struct Description
		{
			int Width = 0;
			int Height = 0;

			FilterMode MinFiltering = FilterMode::Linear;
			FilterMode MagFiltering = FilterMode::Linear;

			WrappingMode HorizontalWrapping = WrappingMode::EdgeClamp;
			WrappingMode VerticalWrapping = WrappingMode::EdgeClamp;

			PixelFormat PixelFormat = PixelFormat::RGBA;
		};

		virtual ~Texture() = default;

		const std::vector<unsigned char>& GetPixelData() const;
		const Description& GetTextureInfo() const;

		void ReleaseMemory();
		virtual void Bind() = 0;

		static Texture* Create(const Texture::Description& desc, const std::string_view filePath);

	protected:

		Texture(const Texture::Description& desc, std::string_view path);

		std::vector<unsigned char>	m_PixelData;
		Description						m_Info;
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
