#pragma once

#include <glm\glm.hpp>

class Camera
{
private: // Camera Attributes
	double m_Yaw, m_Pitch;
	glm::vec3 m_Position;
	glm::vec3 m_CameraUp;
	glm::vec3 m_CameraRight;
	glm::vec3 m_CameraFront;
private:
	float cameraTurnSpeed = 0.2f;
	float cameraMoveSpeed = 0.1f;
private: // Mouse Related
	float mouseSensitivity;
	float mouseDampingSpeed; 
public:
	bool started = false;
	double mouseLastX = 0, mouseLastY = 0;
public:
	Camera(double p_Yaw = -90.0f, double p_Pitch = 0, glm::vec3 p_Position = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 p_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3 p_CameraRight = glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3 p_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f));
	~Camera() = default;
	Camera(Camera& rCamera);

	glm::mat4 GetViewMatrix();
	void Update(double mouseX, double mouseY);

	Camera& operator=(Camera& rCamera);
public:
	void SetMouseSensitivity(float newSensitivity);
public:
	double GetYaw() const;
	double GetPitch() const;
	glm::vec3& GetCameraPosition();
	glm::vec3& GetCameraUp();
	glm::vec3& GetCameraRight();
	glm::vec3& GetCameraFront();
	float GetCameraMoveSpeed() const;
	float GetCameraTurnSpeed() const;

	// Mouse Related
	double GetMouseLastX() const;
	double GetMouseLastY() const;
	float GetMouseSensitivity() const;
	float GetMouseDampingSpeed() const;
};



