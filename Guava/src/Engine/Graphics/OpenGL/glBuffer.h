#pragma once
#include "Engine/Graphics/BufferLayout.h"

namespace Guava::OpenGL
{
	class glBuffer
	{
	public:

		glBuffer(const GLenum target, const GLenum usage);
		~glBuffer();

		void Bind() const;
		void SetData(const void* data, size_t elementSize, size_t elementCount);

		size_t GetElementCount() const;

		virtual void SetLayout(const Guava::Buffer::Layout& layout, const glBuffer* previous = nullptr);

	protected:

		bool m_Instanced = false;

	private:

		GLuint	m_OpenGLHandle = -1;
		GLint	m_LastIndexUsed = -1;
		size_t	m_CurrentSize = 0;
		size_t	m_ElementCount = 0;
		GLenum	m_Target;
		GLenum	m_Usage;
	};

	class glVertexBuffer : public glBuffer
	{
	public:

		glVertexBuffer();
	};

	class glInstanceBuffer : public glBuffer
	{
	public:

		glInstanceBuffer();
	};

	class glIndexBuffer : public glBuffer
	{
	public:

		glIndexBuffer();

	private:

		void SetLayout(const Guava::Buffer::Layout& layout, const glBuffer* previous = nullptr) override {};
	};
}
