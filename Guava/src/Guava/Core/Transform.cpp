#include "pch.h"
#include "Transform.h"

namespace Guava
{
	// Forbidden values
	constexpr glm::vec3 forbAxis(0.0f);

	// Identity matrix
	constexpr glm::mat4 identity(1.0f);

	Transform::Transform() : 
		m_NeedsUpdate		(true),
		m_Transform			(identity),
		m_Translation		(identity),
		m_Rotation			(identity),
		m_Scaling			(identity),
		m_NormalTransform	(glm::transpose(glm::inverse(m_Transform)))
	{
	}

	void Transform::SetPosition(const glm::vec3& position)
	{
		m_Translation = glm::translate(position);

		m_NeedsUpdate = true;
	}

	void Transform::SetPosition(const float x, const float y, const float z)
	{
		m_Translation = glm::translate(glm::vec3(x, y ,z));

		m_NeedsUpdate = true;
	}

	void Transform::SetScale(const glm::vec3& scale)
	{
		m_Scaling = glm::scale(scale);

		m_NeedsUpdate = true;
	}

	void Transform::SetScale(const float scale)
	{
		m_Scaling = glm::scale(glm::vec3(scale));

		m_NeedsUpdate = true;
	}

	void Transform::SetRotation(const float degrees, const glm::vec3& axis)
	{
		m_Rotation = glm::rotate(glm::radians(degrees), axis);

		m_NeedsUpdate = true;
	}

	void Transform::Move(const glm::vec3& offset)
	{
		m_Translation = glm::translate(m_Translation, offset);

		m_NeedsUpdate = true;
	}

	void Transform::Move(const float x, const float y, const float z)
	{
		m_Translation = glm::translate(m_Translation, glm::vec3(x, y, z));

		m_NeedsUpdate = true;
	}

	void Transform::Scale(const glm::vec3& factor)
	{
		m_Scaling = glm::scale(m_Scaling, factor);

		m_NeedsUpdate = true;
	}

	void Transform::Scale(const float factor)
	{
		m_Scaling = glm::scale(m_Scaling, glm::vec3(factor));

		m_NeedsUpdate = true;
	}

	void Transform::Rotate(const float degrees, const glm::vec3& axis)
	{
		m_Rotation = glm::rotate(m_Rotation, glm::radians(degrees), axis);

		m_NeedsUpdate = true;
	}

	const glm::vec3 Transform::GetPosition() const
	{
		return m_Translation[3];
	}

	const glm::vec3 Transform::GetScale() const
	{
		return
		{
			m_Scaling[0][0],
			m_Scaling[1][1],
			m_Scaling[2][2]
		};
	}

	const glm::mat4 Transform::GetRotation() const
	{
		return m_Rotation;
	}

	const glm::mat4& Transform::GetTransform()
	{
		Update();

		return m_Transform;
	}

	const glm::mat3& Transform::GetNormalTransform()
	{
		Update();

		return m_NormalTransform;
	}

	void Transform::Update()
	{
		if (m_NeedsUpdate)
		{
			PreUpdate();

			m_Transform = m_Translation * m_Rotation * m_Scaling;

			m_NormalTransform = glm::transpose(glm::inverse(m_Transform));

			m_NeedsUpdate = false;

			PostUpdate();
		}
	}

	void Transform::PreUpdate()
	{
	}

	void Transform::PostUpdate()
	{
	}
}
