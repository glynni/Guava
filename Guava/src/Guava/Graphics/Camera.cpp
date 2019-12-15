#include "pch.h"
#include "Camera.h"

namespace Guava
{
	static constexpr glm::vec3 s_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	static constexpr glm::vec4 s_Forward = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
	static constexpr glm::vec4 s_Right = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);

	FreeFlyCamera::FreeFlyCamera(const glm::vec3& pos, const glm::vec3& lookAtDir) :
		m_ViewMatrix(),
		m_EyePosition(pos),
		m_LookAtDir(lookAtDir),
		m_PitchAngle(0.0f),
		m_YawAngle(0.0f),
		m_MoveVector(0.0f),
		m_Speed(1.0f),
		m_RotationSpeed(1.0f),
		m_NeedsUpdate(true)
	{
		auto xz_vector = glm::normalize(glm::vec2(lookAtDir.x, lookAtDir.z));
		m_YawAngle = glm::mod(glm::degrees(acos(glm::dot(xz_vector, glm::vec2(0.0f, -1.0f)))), 360.f);

		auto yz_vector = glm::normalize(glm::vec2(lookAtDir.y, lookAtDir.z));
		m_PitchAngle = glm::degrees(acos(glm::dot(yz_vector, glm::vec2(1.0f, -1.0f))));

		if (m_PitchAngle > 90.f)
			m_PitchAngle = 180.f - m_PitchAngle;
		else if (m_PitchAngle < -90.f)
			m_PitchAngle = -180.f - m_PitchAngle;

		m_PitchAngle = glm::clamp(m_PitchAngle, -89.5f, 89.5f);

	}

	const glm::mat4& FreeFlyCamera::GetViewMatrix()
	{
		Update();

		return m_ViewMatrix;
	}

	const glm::vec3& FreeFlyCamera::GetEyePosition()
	{
		Update();

		return m_EyePosition;
	}

	void FreeFlyCamera::Yaw(const float degrees)
	{
		m_YawAngle += degrees * m_RotationSpeed;
		m_YawAngle = glm::mod(m_YawAngle, 360.f);

		m_NeedsUpdate = true;
	}

	void FreeFlyCamera::Pitch(const float degrees)
	{
		m_PitchAngle += degrees * m_RotationSpeed;
		m_PitchAngle = glm::clamp(m_PitchAngle, -89.5f, 89.5f);

		m_NeedsUpdate = true;
	}

	void FreeFlyCamera::SetMoveSpeed(const float speed)
	{
		m_Speed = speed;
	}

	void FreeFlyCamera::SetRotationSpeed(const float speed)
	{
		m_RotationSpeed = speed;
	}

	void FreeFlyCamera::Move(const float x, const float y, const float z)
	{
		m_MoveVector.x += x;
		m_MoveVector.y += y;
		m_MoveVector.z += z;

		m_NeedsUpdate = true;
	}

	void FreeFlyCamera::Update()
	{
		if (m_NeedsUpdate)
		{
			const glm::mat4 yawRotation = glm::rotate(glm::radians(m_YawAngle), s_Up);
			const glm::vec3 actualRight = glm::normalize(yawRotation * s_Right);

			const glm::mat4 fullRotation = glm::rotate(glm::radians(m_PitchAngle), actualRight) * yawRotation;
			const glm::vec3 actualForward = glm::normalize(fullRotation * s_Forward);

			const glm::vec3 offset = {
				actualRight		* m_MoveVector.x +
				s_Up			* m_MoveVector.y +
				actualForward	* m_MoveVector.z };

			m_EyePosition += offset * m_Speed;

			m_ViewMatrix = glm::lookAt(
				m_EyePosition,
				m_EyePosition + actualForward,
				s_Up );

			m_MoveVector = glm::vec3(0.0f);
			m_NeedsUpdate = false;
		}
	}
}