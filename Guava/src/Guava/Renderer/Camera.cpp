#include "pch.h"
#include "Camera.h"

namespace Guava
{
	Camera::Camera() :

		m_Position(glm::vec3(0.0f, 0.0f, 3.0f)),

		m_ForwardVector(glm::vec3(0.0f, 0.0f, -1.0f)),	// Z axis points into camera
		m_RightVector(glm::vec3(1.0f, 0.0f, 0.0f)),

		m_MoveVector(glm::vec3(0.0f)),

		m_ViewMatrix(glm::lookAt(m_Position, m_Position + m_ForwardVector, m_UpVector)),

		m_UnitsPerSecond(200.f),
		m_RotationSpeed(0.2f),

		m_Pitch(0.0f),
		m_Yaw(90.0f),

		m_Changed(true),
		m_MoveLeft(false),
		m_MoveRight(false),
		m_MoveBackwards(false),
		m_MoveForwards(false),
		m_MoveUpwards(false),
		m_MoveDownwards(false)
	{
	}

	void Camera::Update(double dt)
	{
		if (m_Changed)
		{
			const float pitch = glm::radians(m_Pitch);
			const float yaw = glm::radians(m_Yaw);

			m_ForwardVector.x = cos(pitch) * cos(yaw);
			m_ForwardVector.y = sin(pitch);
			m_ForwardVector.z = cos(pitch) * sin(yaw);
			m_ForwardVector = -normalize(m_ForwardVector);

			m_MoveVector = glm::vec3(0.0f);
			m_RightVector = -normalize(cross(m_UpVector, m_ForwardVector));

			if (m_MoveForwards)
				m_MoveVector += m_ForwardVector;

			if (m_MoveBackwards)
				m_MoveVector -= m_ForwardVector;

			if (m_MoveLeft)
				m_MoveVector -= m_RightVector;

			if (m_MoveRight)
				m_MoveVector += m_RightVector;

			if (m_MoveUpwards)
				m_MoveVector += m_UpVector;

			if (m_MoveDownwards)
				m_MoveVector -= m_UpVector;

			if(length(m_MoveVector) != 0.f)
				m_MoveVector = normalize(m_MoveVector) * m_UnitsPerSecond * (float)dt;

			m_Position += m_MoveVector;

			m_ViewMatrix = lookAt(m_Position, m_Position + m_ForwardVector, m_UpVector);

			m_MoveLeft = false;
			m_MoveRight = false;
			m_MoveBackwards = false;
			m_MoveForwards = false;
			m_MoveUpwards = false;
			m_MoveDownwards = false;

			m_Changed = false;
		}
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		m_Changed = true;
	}

	void Camera::SetMoveSpeed(float unitsPerSec)
	{
		m_UnitsPerSecond = unitsPerSec;
	}

	void Camera::SetRotationSpeed(float speed)
	{
		m_RotationSpeed = speed;
	}

	void Camera::MoveLeft()
	{
		m_MoveLeft = m_Changed = true;
	}

	void Camera::MoveRight()
	{
		m_MoveRight = m_Changed = true;
	}

	void Camera::MoveBackwards()
	{
		m_MoveBackwards = m_Changed = true;
	}

	void Camera::MoveForwards()
	{
		m_MoveForwards = m_Changed = true;
	}

	void Camera::MoveUpwards()
	{
		m_MoveUpwards = m_Changed = true;
	}

	void Camera::MoveDownWards()
	{
		m_MoveDownwards = m_Changed = true;
	}

	void Camera::Pitch(float pitch)
	{
		if (pitch != 0.f){

			m_Pitch -= (pitch * m_RotationSpeed);

			// Don't touch up vector
			if (m_Pitch > 89.f)
				m_Pitch = 89.f;
			else if (m_Pitch < -89.f)
				m_Pitch = -89.f;

			m_Changed = true;
		}
	}

	void Camera::Yaw(float yaw)
	{
		if (yaw != 0.f) {

			m_Yaw = glm::mod(m_Yaw -= (yaw * m_RotationSpeed), 360.f);
			m_Changed = true;
		}
	}

	const glm::mat4& Camera::GetViewMatrix() const
	{
		return m_ViewMatrix;
	}
}