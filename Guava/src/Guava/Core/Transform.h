#pragma once
#include "Guava/Core/Core.h"

namespace Guava
{
	class  Transform
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

		// Apply a scaling factor to the current scale (multiplicatively)
		void Scale(const vec3& factor);
		void Scale(const float factor);

		// Add the given angle to the current rotation (additively)
		void Rotate(const float degrees, const vec3& axis);

		const vec3 GetPosition() const;
		const vec3 GetScale() const;
		const mat4 GetRotation() const;

		const mat4& GetTransform();
		const mat3& GetNormalTransform();

	protected:

		mat4	m_Translation;
		mat4	m_Rotation;
		mat4	m_Scaling;
		mat4	m_Transform;
		mat3	m_NormalTransform;

		bool		m_UpdateTransform;
		bool		m_UpdateNormalTransform;

		void Update();

		virtual void PreUpdate();
		virtual void PostUpdate();
	};
}