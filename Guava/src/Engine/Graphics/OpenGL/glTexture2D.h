#pragma once
#include "../Texture2D.h"

namespace Guava::OpenGL
{
	class glTexture2D : public Guava::Texture2D
	{
	public:

		glTexture2D(const Texture2DCreateInfo& description);
		~glTexture2D();

		void Bind(TextureSlot slot) override;

	private:

		GLuint m_Texture;
		bool   m_Initialized;

		void CreateStorage();
		void SetTextureParameter(GLenum id, GLint parameter);

		void GPU_UpdateData() override;
	};
}