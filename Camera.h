#pragma once

namespace SheeEngine
{
	using vec3 = glm::vec3;
	using mat4 = glm::mat4;


	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float CAMERASPEED = 5.0f;
	const float SENSITIVITY = 0.1f;
	const float FOV = 45.0f;

	class Camera
	{
	public:
		// Constructor
		Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f), 
			vec3 worldup = vec3(0.0f, 1.0f, 0.0f));

		Camera(float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, 
			float worldupX = 0.0f, float worldupY = 1.0f, float worldupZ = 0.0f);

		
		mat4 getViewMatrix()
		{
			return glm::lookAt(Position, Position + Front, Up);
		}

		// Camera Movement
		inline void MoveForward(float deltaTime);
		inline void MoveBackward(float deltaTime);
		inline void MoveLeft(float deltaTime);
		inline void MoveRight(float deltaTime);
		inline void MoveUp(float deltaTime);
		inline void MoveDown(float deltaTime);

		// Camera View Movement
		void LookAround_Callback(double xPos, double yPos, float windowSizeX, float windowSizeY);

		// Camera Field Of View Change by Mouse Scroll
		void ScrollFOV_Callback(double yOffset);

		// Get
		inline vec3 GetPosition()               const { return Position; }
		inline vec3 GetFrontVec()               const { return Front; }
		inline vec3 GetUpVec()                  const { return Up; }
		inline vec3 GetRightVec()               const { return Right; }
											    
		inline float GetCameraYaw()             const { return Yaw; }
		inline float GetCameraPitch()           const { return Pitch; }
											    
		inline float GetCameraSpeed()           const { return CameraSpeed; }
		inline float GetMouseSensitivity()      const { return MouseSensitivity; }
		inline float GetCameraFieldOfView()     const { return Fov; }

		// Set
		inline float SetCameraSpeed(float speed)				{ CameraSpeed = speed; }
		inline float SetMouseSensitivity(float sensitivity)		{ MouseSensitivity = sensitivity; }
		inline float SetCameraFieldOfView(float fov)			{ Fov = fov; }

	private:
		vec3 Position;
		vec3 Front;
		vec3 Up;
		vec3 Right;
		vec3 WorldUp;

		float Yaw = YAW;
		float Pitch = PITCH;

		float CameraSpeed = CAMERASPEED;
		float MouseSensitivity = SENSITIVITY;
		float Fov = FOV;

		// calculate the current vector of camera
		void UpdateCameraVectors();
	};
}

