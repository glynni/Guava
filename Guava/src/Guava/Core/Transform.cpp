#include "pch.h"
#include "Transform.h"

namespace Guava
{
	// Forbidden values
	constexpr glm::vec3 forbAxis(0.0f);

	// Identity matrix
	constexpr glm::mat4 identity(1.0f);

	Transform::Transform() : 
		m_NeedsUpdate	 (true),
		m_Transformation (identity),
		m_Position		 (glm::vec3(0.0f)),
		m_Scale			 (glm::vec3(1.0f)),
		m_Rotation		 (Rotation())
	{
	}

	void Transform::SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
		m_NeedsUpdate = true;
	}

	void Transform::SetRotation(const float degrees, const glm::vec3& axis)
	{
		if (axis == forbAxis) return;

		m_Rotation.Axis = axis;
		m_Rotation.Degrees = degrees;
		m_NeedsUpdate = true;
	}

	void Transform::SetRotation(const Rotation& rotation)
	{
		if (rotation.Axis == forbAxis) return;

		m_Rotation = rotation;
		m_NeedsUpdate = true;
	}

	void Transform::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		m_NeedsUpdate = true;
	}

	void Transform::Move(const glm::vec3& offset)
	{
		m_Position += offset;
		m_NeedsUpdate = true;
	}

	void Transform::Scale(const glm::vec3& factor)
	{
		m_Scale *= factor;
		m_NeedsUpdate = true;
	}

	void Transform::Rotate(const float degrees)
	{
		m_Rotation.Degrees = glm::mod(m_Rotation.Degrees + degrees, 360.f);
		m_NeedsUpdate = true;
	}

	const glm::vec3& Transform::GetScale() const
	{
		return m_Scale;
	}

	const Rotation& Transform::GetRotation() const
	{
		return m_Rotation;
	}

	const glm::vec3& Transform::GetPosition() const
	{
		return m_Position;
	}

	const glm::mat4& Transform::GetTransform() const
	{
		if (m_NeedsUpdate)
		{
			m_Transformation = 
				glm::translate(identity, m_Position) *
				glm::rotate(identity, glm::radians(m_Rotation.Degrees), m_Rotation.Axis) *
				glm::scale(identity, m_Scale);

			m_NeedsUpdate = false;
		}

		return m_Transformation;
	}

	Rotation::Rotation() :
		Axis	(glm::vec3(0.0f, 1.0f, 0.0f)),
		Degrees	(0.0f)
	{
	}
}
