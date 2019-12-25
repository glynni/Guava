#pragma once

namespace Guava
{
	class Camera
	{
	public:

		virtual ~Camera() = default;

		virtual const mat4& GetViewMatrix() = 0;
		virtual const vec3& GetEyePosition() = 0;
	};

	class FreeFlyCamera : public Camera
	{
	public:

		FreeFlyCamera(const vec3& pos = vec3(), const vec3& lookAtDir = vec3(0.0f, 0.0f, -1.0f));

		const mat4& GetViewMatrix() override;
		const vec3& GetEyePosition() override;

		void Yaw(const float degrees);
		void Pitch(const float degrees);

		void SetMoveSpeed(const float speed);
		void SetRotationSpeed(const float speed);

		// right, up, forward
		void Move(const float x, const float y, const float z);

	private:

		mat4 m_ViewMatrix;

		vec3 m_EyePosition;
		vec3 m_LookAtDir;
		vec3 m_MoveVector;

		float m_PitchAngle;
		float m_YawAngle;

		float m_Speed;
		float m_RotationSpeed;

		bool m_NeedsUpdate;

		void Update();
	};
}