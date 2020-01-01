#include "Camera.h"
#include "Utils.hpp"

#include <glm\gtc\matrix_transform.hpp>


using namespace Utils;
const float toRadians = 3.14f / 180.0f;
Camera::Camera(double p_Yaw, double p_Pitch, glm::vec3 p_Position, glm::vec3 p_CameraUp,
	glm::vec3 p_CameraRight, glm::vec3 p_CameraFront)
	: m_Yaw(p_Yaw), m_Pitch(p_Pitch), m_Position(p_Position), m_CameraUp(p_CameraUp), m_CameraRight(p_CameraRight), m_CameraFront(p_CameraFront),
	  mouseSensitivity(0.05f), mouseDampingSpeed(5) { }

Camera::Camera(Camera& rCamera)
{
	m_Yaw = rCamera.GetYaw();
	m_Pitch = rCamera.GetPitch();
	m_Position = rCamera.GetCameraPosition();
	m_CameraUp = rCamera.GetCameraUp();
	m_CameraRight = rCamera.GetCameraRight();
	m_CameraFront = rCamera.GetCameraFront();

	mouseSensitivity = rCamera.GetMouseSensitivity();
	mouseDampingSpeed = rCamera.GetMouseDampingSpeed();
}

Camera& Camera::operator=(Camera& rCamera)
{
	if (this != &rCamera)
	{
		Camera newCamera(rCamera);
		return newCamera;
	}
	return *this;
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_Position, m_Position + m_CameraFront, m_CameraUp);
}

void Camera::Update(double mouseX, double mouseY)
{
	//std::cout << mouseLastX << " " << mouseX << "\n" << mouseLastY << mouseY << "\n\n";
	if (!started)
	{
		started = true;
		mouseLastX = mouseX;
		mouseLastY = mouseY;
	}

	double diffX = (mouseLastX - mouseX) * cameraTurnSpeed;
	double diffY = (mouseLastY - mouseY) * cameraTurnSpeed;
	
	m_Yaw -= diffX;
	m_Pitch = Utils::Clamp<double>(m_Pitch + diffY, -89.0f, 89.0f);

	mouseLastX = mouseX;
	mouseLastY = mouseY;

	m_CameraFront = glm::vec3(cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)), sin(glm::radians(m_Pitch)), sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)));
	m_CameraFront = glm::normalize(m_CameraFront);
	
	m_CameraRight = glm::normalize(glm::cross(m_CameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));
	m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));


	// Update yaw pitch and recalculate 
	// Local axes of the camera

	// Get current mouseX take diff and add it to yaw
	// Same for y and add it to pitch
	// Update lastX lastY
	// recalculate Z X Y

	// Recalculate front
}

// Setters
void Camera::SetMouseSensitivity(float newSensitivity) { mouseSensitivity = newSensitivity; }
// Getters
double Camera::GetYaw() const { return m_Yaw; }
double Camera::GetPitch() const { return m_Pitch; }
glm::vec3& Camera::GetCameraPosition() { return m_Position; }
glm::vec3& Camera::GetCameraUp() { return m_CameraUp; }
glm::vec3& Camera::GetCameraRight() { return m_CameraRight; }
glm::vec3& Camera::GetCameraFront() { return m_CameraFront; }
float Camera::GetCameraMoveSpeed() const { return cameraMoveSpeed; }
float Camera::GetCameraTurnSpeed() const { return cameraTurnSpeed; }
// Mouse Related
double Camera::GetMouseLastX() const { return mouseLastX; }
double Camera::GetMouseLastY() const { return mouseLastY; }
float Camera::GetMouseSensitivity() const { return mouseSensitivity; }
float Camera::GetMouseDampingSpeed() const { return mouseDampingSpeed; }
//




//