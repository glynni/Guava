#pragma once
#include "Engine/Core/Core.h"

namespace Guava
{
	class Transform
	{
	public:

		Transform();

		void SetPosition(const vec3& position);
		void SetPosition(const float x, const float y, const float z);
		void SetScale(const vec3& scale);
		void SetScale(const float scale);
		void SetRotation(const float degrees, const vec3& axis);

		// Applies the given offset to current position
		void Move(const vec3& offset);
		void Move(const float x, const float y, const float z);

		// Add the given angle to the current rotation (additively)
		void Rotate(const float degrees, const vec3& axis);

		const vec3& GetPosition() const;
		const vec3	GetScale() const;
		const mat4& GetRotation() const;

		const mat4& GetMatrix();
		const mat3& GetNormalMatrix();

	protected:

		mat4	m_Translation;
		mat4	m_Rotation;
		mat4	m_Scaling;

		mat4	m_Matrix;
		mat3	m_NormalMatrix;

		bool	m_UpdateMatrix;
		bool	m_UpdateNormalMatrix;

		void Update();
	};
}