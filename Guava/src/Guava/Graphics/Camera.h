#pragma once

namespace Guava
{
	class Camera
	{
	public:

		virtual ~Camera() = default;

		virtual const glm::mat4& GetViewMatrix() = 0;
		virtual const glm::vec3& GetEyePosition() = 0;
	};

	class FreeFlyCamera : public Camera
	{
	public:

		FreeFlyCamera(const glm::vec3& pos = glm::vec3(), const glm::vec3& lookAtDir = glm::vec3(0.0f, 0.0f, -1.0f));

		const glm::mat4& GetViewMatrix() override;
		const glm::vec3& GetEyePosition() override;

		void Yaw(const float degrees);
		void Pitch(const float degrees);

		void SetMoveSpeed(const float speed);
		void SetRotationSpeed(const float speed);

		// right, up, forward
		void Move(const float x, const float y, const float z);

	private:

		glm::mat4 m_ViewMatrix;

		glm::vec3 m_EyePosition;
		glm::vec3 m_LookAtDir;
		glm::vec3 m_MoveVector;

		float m_PitchAngle;
		float m_YawAngle;

		float m_Speed;
		float m_RotationSpeed;

		bool m_NeedsUpdate;

		void Update();
	};
}