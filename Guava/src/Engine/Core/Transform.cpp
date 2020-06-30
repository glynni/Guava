#include "pch.h"
#include "Transform.h"

namespace Guava
{
	// Forbidden values
	constexpr vec3 forbAxis(0.0f);

	// Identity matrix
	constexpr mat4 identity(1.0f);

	Transform::Transform() : 
		m_UpdateMatrix	(true),
		m_UpdateNormalMatrix	(true),
		m_Matrix			(identity),
		m_Translation		(identity),
		m_Rotation			(identity),
		m_Scaling			(identity),
		m_NormalMatrix	(transpose(inverse(m_Matrix)))
	{
	}

	void Transform::SetPosition(const vec3& position)
	{
		m_Translation = translate(position);

		m_UpdateMatrix = true;
	}

	void Transform::SetPosition(const float x, const float y, const float z)
	{
		m_Translation = translate(vec3(x, y ,z));

		m_UpdateMatrix = true;
	}

	void Transform::SetScale(const vec3& sc)
	{
		m_Scaling = scale(sc);

		m_UpdateMatrix = true;
	}

	void Transform::SetScale(const float sc)
	{
		m_Scaling = scale(vec3(sc));

		m_UpdateMatrix = true;
	}

	void Transform::SetRotation(const float degrees, const vec3& axis)
	{
		m_Rotation = rotate(radians(degrees), axis);

		m_UpdateMatrix = true;
	}

	void Transform::Move(const vec3& offset)
	{
		m_Translation = translate(identity, offset) * m_Translation;

		m_UpdateMatrix = true;
	}

	void Transform::Move(const float x, const float y, const float z)
	{
		m_Translation = translate(identity, vec3(x, y, z)) * m_Translation;

		m_UpdateMatrix = true;
	}

	void Transform::Rotate(const float degrees, const vec3& axis)
	{
		m_Rotation = rotate(identity, radians(degrees), axis) * m_Rotation;

		m_UpdateMatrix = true;
	}

	const vec3& Transform::GetPosition() const
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

	const mat4& Transform::GetRotation() const
	{
		return m_Rotation;
	}

	const mat4& Transform::GetMatrix()
	{
		Update();

		return m_Matrix;
	}

	const mat3& Transform::GetNormalMatrix()
	{
		Update();

		if (m_UpdateNormalMatrix)
		{
			m_NormalMatrix = transpose(inverse(m_Matrix));
			m_UpdateNormalMatrix = false;
		}

		return m_NormalMatrix;
	}

	void Transform::Update()
	{
		if (m_UpdateMatrix)
		{
			m_Matrix = m_Translation * m_Rotation * m_Scaling;

			m_UpdateNormalMatrix = true;
			m_UpdateMatrix = false;
		}
	}
}
