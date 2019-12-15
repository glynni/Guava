#pragma once
#include "Guava/Core/Core.h"

namespace Guava
{
	class  Transform
	{
	public:

		Transform();

		void SetPosition(const glm::vec3& position);
		void SetPosition(const float x, const float y, const float z);
		void SetScale(const glm::vec3& scale);
		void SetScale(const float scale);
		void SetRotation(const float degrees, const glm::vec3& axis);

		// Applies the given offset to current position
		void Move(const glm::vec3& offset);
		void Move(const float x, const float y, const float z);

		// Apply a scaling factor to the current scale (multiplicatively)
		void Scale(const glm::vec3& factor);
		void Scale(const float factor);

		// Add the given angle to the current rotation (additively)
		void Rotate(const float degrees, const glm::vec3& axis);

		const glm::vec3 GetPosition() const;
		const glm::vec3 GetScale() const;
		const glm::mat4 GetRotation() const;

		const glm::mat4& GetTransform();
		const glm::mat3& GetNormalTransform();

	protected:

		glm::mat4	m_Translation;
		glm::mat4	m_Rotation;
		glm::mat4	m_Scaling;
		glm::mat4	m_Transform;
		glm::mat3	m_NormalTransform;

		bool		m_NeedsUpdate;

		void Update();

		virtual void PreUpdate();
		virtual void PostUpdate();
	};
}