#pragma once
#include <glm.hpp>

namespace Guava
{
	class Camera
	{
	public:

		Camera();
		~Camera(){}

		void Update(double dt);

		void SetPosition(const glm::vec3& position);
		void SetMoveSpeed(float unitsPerSec);
		void SetRotationSpeed(float speed);

		void MoveLeft();	
		void MoveRight();	
		void MoveBackwards();
		void MoveForwards();
		void MoveUpwards();
		void MoveDownWards();

		void Pitch(float pitch);
		void Yaw(float yaw);

		const glm::mat4& GetViewMatrix() const;

	private:

		bool	m_Changed;

		bool	m_MoveLeft;
		bool	m_MoveRight;
		bool	m_MoveBackwards;
		bool	m_MoveForwards;
		bool	m_MoveUpwards;
		bool	m_MoveDownwards;

		float	m_UnitsPerSecond;
		float	m_RotationSpeed;

		float	m_Pitch;
		float	m_Yaw;

		glm::vec3	m_Position;			// Point
		glm::vec3	m_MoveVector;		// Direction
		glm::vec3	m_ForwardVector;	// Direction
		glm::vec3	m_RightVector;		// Direction

		glm::mat4	m_ViewMatrix;

		constexpr static glm::vec3 m_UpVector = glm::vec3(0.0f, 1.0f, 0.0f);
	};
}