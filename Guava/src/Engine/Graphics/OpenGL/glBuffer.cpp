#include "pch.h"
#include "glBuffer.h"

namespace Guava::OpenGL
{
	static GLenum GetGLType(Guava::Buffer::Attribute::Type type)
	{
		switch (type)
		{
		case Guava::Buffer::Attribute::Type::Vec2f:
		case Guava::Buffer::Attribute::Type::Vec3f:
		case Guava::Buffer::Attribute::Type::Vec4f:
		case Guava::Buffer::Attribute::Type::Mat4f:
			return GL_FLOAT;

		default:
			GUAVA_ASSERT(false, "Wrong Attributetype specified!");
			return GL_FLOAT;
		}
	}

	static void ApplyAttribute(GLuint vaaIndex, GLenum type, GLuint numElements, size_t stride, GLuint offset, bool instanced)
	{
		glEnableVertexAttribArray(vaaIndex);
		glVertexAttribPointer(vaaIndex, numElements, type, false, stride, (void*)offset);

		if (instanced)
			glVertexAttribDivisor(vaaIndex, 1);
	}

	glBuffer::~glBuffer()
	{
		glDeleteBuffers(1, &m_OpenGLHandle);
	}

	void glBuffer::SetData(const void* data, size_t elementSize, size_t elementCount)
	{
		// glMapBuffer, glUnmapBuffer are also worth exploring

		Bind();

		m_ElementCount = elementCount;

		size_t newSize = elementSize * elementCount;

		if (newSize > m_CurrentSize)
		{
			glBufferData(m_Target, newSize, data, m_Usage);
			m_CurrentSize = newSize;
		}
		else
		{
			glBufferSubData(m_Target, 0, newSize, data);
		}
	}

	size_t glBuffer::GetElementCount() const
	{
		return m_ElementCount;
	}

	void glBuffer::Bind() const
	{
		glBindBuffer(m_Target, m_OpenGLHandle);
	}

	void glBuffer::SetLayout(const Guava::Buffer::Layout& layout, const glBuffer* previous)
	{
		Bind();

		bool modified = false;
		GLint vaaBaseIndex;

		if (previous)
			vaaBaseIndex = previous->m_LastIndexUsed + 1;
		else
			vaaBaseIndex = 0;

		for (auto& attribute : layout.Attributes)
		{
			GLenum glType = GetGLType(attribute.AttributeType);

			if (attribute.NumElements <= 4)
			{
				ApplyAttribute(vaaBaseIndex, glType, attribute.NumElements, layout.Stride, attribute.Offset, m_Instanced);
				++vaaBaseIndex;

				modified = true;
			}
			else
			{
				unsigned int numFull = attribute.NumElements / 4;
				unsigned int rest = attribute.NumElements % 4;
				size_t sizeElementar = attribute.Size / attribute.NumElements;
				size_t fakeOffset = attribute.Offset;

				for (unsigned int i = 0; i < numFull; ++i)
				{
					ApplyAttribute(vaaBaseIndex, glType, 4, layout.Stride, fakeOffset, m_Instanced);
					fakeOffset += 4 * sizeElementar;
					++vaaBaseIndex;

					modified = true;
				}

				if (rest > 0)
				{
					ApplyAttribute(vaaBaseIndex, glType, rest, layout.Stride, fakeOffset, m_Instanced);
					fakeOffset += rest * sizeElementar;
					++vaaBaseIndex;

					modified = true;
				}
			}
		}

		if (modified)
			m_LastIndexUsed = vaaBaseIndex - 1;
	}

	glBuffer::glBuffer(const GLenum target, const GLenum usage) :
		m_Target(target),
		m_Usage(usage)
	{
		glGenBuffers(1, &m_OpenGLHandle);

		m_Instanced = false;
	}
	
	glIndexBuffer::glIndexBuffer() : glBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW)
	{
		m_Instanced = false;
	}

	glVertexBuffer::glVertexBuffer() : glBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW)
	{
		m_Instanced = false;
	}

	glInstanceBuffer::glInstanceBuffer() : glBuffer(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW)
	{
		m_Instanced = true;
	}
}
