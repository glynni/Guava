#include "pch.h"
#include "Camera.h"

namespace Guava
{
	static constexpr vec3 s_Up = vec3(0.0f, 1.0f, 0.0f);
	static constexpr vec4 s_Forward = vec4(0.0f, 0.0f, -1.0f, 0.0f);
	static constexpr vec4 s_Right = vec4(1.0f, 0.0f, 0.0f, 0.0f);

	FreeFlyCamera::FreeFlyCamera(const vec3& pos, const vec3& lookAtDir) :
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
		auto xz_vector = normalize(vec2(lookAtDir.x, lookAtDir.z));
		m_YawAngle = mod(degrees(acos(dot(xz_vector, vec2(0.0f, -1.0f)))), 360.f);

		auto yz_vector = normalize(vec2(lookAtDir.y, lookAtDir.z));
		m_PitchAngle = degrees(acos(dot(yz_vector, vec2(1.0f, -1.0f))));

		if (m_PitchAngle > 90.f)
			m_PitchAngle = 180.f - m_PitchAngle;
		else if (m_PitchAngle < -90.f)
			m_PitchAngle = -180.f - m_PitchAngle;

		m_PitchAngle = clamp(m_PitchAngle, -89.5f, 89.5f);

	}

	const mat4& FreeFlyCamera::GetViewMatrix()
	{
		Update();

		return m_ViewMatrix;
	}

	const vec3& FreeFlyCamera::GetEyePosition()
	{
		Update();

		return m_EyePosition;
	}

	void FreeFlyCamera::Yaw(const float degrees)
	{
		m_YawAngle += degrees * m_RotationSpeed;
		m_YawAngle = mod(m_YawAngle, 360.f);

		m_NeedsUpdate = true;
	}

	void FreeFlyCamera::Pitch(const float degrees)
	{
		m_PitchAngle += degrees * m_RotationSpeed;
		m_PitchAngle = clamp(m_PitchAngle, -89.5f, 89.5f);

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
			const mat4 yawRotation = rotate(radians(m_YawAngle), s_Up);
			const vec3 actualRight = normalize(yawRotation * s_Right);

			const mat4 fullRotation = rotate(radians(m_PitchAngle), actualRight) * yawRotation;
			const vec3 actualForward = normalize(fullRotation * s_Forward);

			const vec3 offset = {
				actualRight		* m_MoveVector.x +
				s_Up			* m_MoveVector.y +
				actualForward	* m_MoveVector.z };

			m_EyePosition += offset * m_Speed;

			m_ViewMatrix = lookAt(
				m_EyePosition,
				m_EyePosition + actualForward,
				s_Up );

			m_MoveVector = vec3(0.0f);
			m_NeedsUpdate = false;

			//GUAVA_TRACE("Camera: {0}, {1}, {2}", m_EyePosition.x, m_EyePosition.y, m_EyePosition.z);
		}
	}
}