#include "pch.h"
#include "Transform.h"

namespace Guava
{
	// Forbidden values
	constexpr vec3 forbAxis(0.0f);

	// Identity matrix
	constexpr mat4 identity(1.0f);

	Transform::Transform() : 
		m_UpdateTransform	(true),
		m_UpdateNormalTransform	(true),
		m_Transform			(identity),
		m_Translation		(identity),
		m_Rotation			(identity),
		m_Scaling			(identity),
		m_NormalTransform	(transpose(inverse(m_Transform)))
	{
	}

	void Transform::SetPosition(const vec3& position)
	{
		m_Translation = translate(position);

		m_UpdateTransform = true;
	}

	void Transform::SetPosition(const float x, const float y, const float z)
	{
		m_Translation = translate(vec3(x, y ,z));

		m_UpdateTransform = true;
	}

	void Transform::SetScale(const vec3& sc)
	{
		m_Scaling = scale(sc);

		m_UpdateTransform = true;
	}

	void Transform::SetScale(const float sc)
	{
		m_Scaling = scale(vec3(sc));

		m_UpdateTransform = true;
	}

	void Transform::SetRotation(const float degrees, const vec3& axis)
	{
		m_Rotation = rotate(radians(degrees), axis);

		m_UpdateTransform = true;
	}

	void Transform::Move(const vec3& offset)
	{
		m_Translation = translate(m_Translation, offset);

		m_UpdateTransform = true;
	}

	void Transform::Move(const float x, const float y, const float z)
	{
		m_Translation = translate(m_Translation, vec3(x, y, z));

		m_UpdateTransform = true;
	}

	void Transform::Scale(const vec3& factor)
	{
		m_Scaling = scale(m_Scaling, factor);

		m_UpdateTransform = true;
	}

	void Transform::Scale(const float factor)
	{
		m_Scaling = scale(m_Scaling, vec3(factor));

		m_UpdateTransform = true;
	}

	void Transform::Rotate(const float degrees, const vec3& axis)
	{
		m_Rotation = rotate(m_Rotation, radians(degrees), axis);

		m_UpdateTransform = true;
	}

	const vec3 Transform::GetPosition() const
	{
		return m_Translation[3];
	}

	const vec3 Transform::GetScale() const
	{
		return
		{
			m_Scaling[0][0],
			m_Scaling[1][1],
			m_Scaling[2][2]
		};
	}

	const mat4 Transform::GetRotation() const
	{
		return m_Rotation;
	}

	const mat4& Transform::GetTransform()
	{
		Update();

		return m_Transform;
	}

	const mat3& Transform::GetNormalTransform()
	{
		Update();

		if (m_UpdateNormalTransform)
		{
			m_NormalTransform = transpose(inverse(m_Transform));
			m_UpdateNormalTransform = false;
		}

		return m_NormalTransform;
	}

	void Transform::Update()
	{
		if (m_UpdateTransform)
		{
			PreUpdate();

			m_Transform = m_Translation * m_Rotation * m_Scaling;

			m_UpdateNormalTransform = true;
			m_UpdateTransform = false;

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
