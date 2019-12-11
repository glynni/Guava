#include "Guava/Core/Core.h"

namespace Guava
{
	struct Rotation
	{
		Rotation();

		glm::vec3 Axis;
		float Degrees;
	};

	class  Transform
	{
	public:

		Transform();

		void SetScale(const glm::vec3& scale);
		void SetRotation(const float degrees, const glm::vec3& axis);
		void SetRotation(const Rotation& rotation);
		void SetPosition(const glm::vec3& position);

		// Applies the given offset to current position
		void Move(const glm::vec3& offset);
		// Apply a scaling factor to the current scale (multiplicatively)
		void Scale(const glm::vec3& factor);
		// Add the given angle to the current rotation (additively)
		void Rotate(const float degrees);

		const glm::vec3& GetScale() const;
		const Rotation& GetRotation() const;
		const glm::vec3& GetPosition() const;

		const glm::mat4& GetTransform() const;

	private:

		glm::vec3			m_Position;
		glm::vec3			m_Scale;
		Rotation			m_Rotation;

		mutable glm::mat4	m_Transformation;
		mutable bool		m_NeedsUpdate;
	};
}