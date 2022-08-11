#include "seafx.h"
#include "Camera.h"

namespace SheeEngine
{

	/******************************************
	* Constructor
	*******************************************/
	Camera::Camera(vec3 position, vec3 worldup)
		: Front(vec3(0.0f, 0.0f, -1.0f)), 
		  Position(position), 
		  WorldUp(worldup)
	{
		UpdateCameraVectors();
	}

	Camera::Camera(float posX, float posY, float posZ, float worldupX, float worldupY, float worldupZ)
		: Front(vec3(0.0f, 0.0f, -1.0f)), 
		  Position(vec3(posX, posY, posZ)), 
		  WorldUp(vec3(worldupX, worldupY, worldupZ))
	{
		UpdateCameraVectors();
	}


	/********************************************
	* Camera Movement
	*********************************************/
	void Camera::MoveForward(float deltaTime)
	{
		Position += Front * (CameraSpeed * deltaTime);
	}

	inline void Camera::MoveBackward(float deltaTime)
	{
		Position -= Front * (CameraSpeed * deltaTime);
	}

	inline void Camera::MoveLeft(float deltaTime)
	{
		Position -= glm::normalize(glm::cross(Front, Up)) * (CameraSpeed * deltaTime);
	}

	inline void Camera::MoveRight(float deltaTime)
	{
		Position += glm::normalize(glm::cross(Front, Up)) * (CameraSpeed * deltaTime);
	}

	void Camera::MoveUp(float deltaTime)
	{
		Position += Up * (CameraSpeed * deltaTime);
	}

	void Camera::MoveDown(float deltaTime)
	{
		Position -= Up * (CameraSpeed * deltaTime);
	}

	/********************************************
	* use in glfw callback register -------- Look Around
	**********************************************/
	bool FirstMouse = true;
	float LastPosX = 0.0f;
	float LastPosY = 0.0f;
	float XOffset = 0.0f;
	float YOffset = 0.0f;
	void Camera::LookAround_Callback(double xPos, double yPos, float windowSizeX, float windowSizeY)
	{
		float MousePosX = static_cast<float>(xPos);
		float MousePosY = static_cast<float>(yPos);

		/* if click the window firstly */
		if (FirstMouse)
		{
			/* set the lastPos as click point */
			LastPosX = MousePosX;
			LastPosY = MousePosY;
			FirstMouse = false;
		}

		XOffset = MousePosX - LastPosX;
		YOffset = LastPosY - MousePosY;

		Yaw += XOffset * MouseSensitivity;
		Pitch += YOffset * MouseSensitivity;

		/* limite range of pitch angle */
		if (Pitch > 89.0f)
		{
			Pitch = 89.0f;
		}
		if (Pitch < -89.0f)
		{
			Pitch = -89.0f;
		}

		/* Update front vector */
		UpdateCameraVectors();

		LastPosX = MousePosX;
		LastPosY = MousePosY;
	}

	/********************************************
	* use in glfw callback register -------- restrict the fov scale
	**********************************************/
	void Camera::ScrollFOV_Callback(double yOffset)
	{
		Fov -= static_cast<float>(yOffset);
		if (Fov > FOV)
		{
			Fov = FOV;
		}
		if (Fov < 1.0f)
		{
			Fov = 1.0f;
		}
	}


	/********************************************
	* For Camera init and front/Right/up vector change in Look around movement
	*********************************************/
	void Camera::UpdateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		/* schimidt orthogonalization */
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}

}
