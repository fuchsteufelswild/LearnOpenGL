#include "KeyCommand.h"
#include "Camera.h"

#include <glm\glm.hpp>

void GoRightCommand::PerformAction(Camera& target)
{
	glm::vec3& camPos = target.GetCameraPosition();
	camPos += target.GetCameraRight() * target.GetCameraMoveSpeed();
}

void GoLeftCommand::PerformAction(Camera& target)
{
	glm::vec3& camPos = target.GetCameraPosition();
	camPos -= target.GetCameraRight() * target.GetCameraMoveSpeed();
}

void GoUpCommand::PerformAction(Camera& target)
{

	glm::vec3 camPos = target.GetCameraPosition();

	camPos.y += target.GetCameraMoveSpeed();
}

void GoDownCommand::PerformAction(Camera& target)
{

	glm::vec3 camPos = target.GetCameraPosition();

	camPos.y -= target.GetCameraMoveSpeed();
}

void GoForwardCommand::PerformAction(Camera& target)
{
	glm::vec3& camPos = target.GetCameraPosition();
	camPos += target.GetCameraFront() * target.GetCameraMoveSpeed();
	// camPos.z -= target.GetCameraMoveSpeed();
}

void GoBackwardCommand::PerformAction(Camera& target)
{

	glm::vec3& camPos = target.GetCameraPosition();
	camPos -= target.GetCameraFront() * target.GetCameraMoveSpeed();
}

void MouseRotateHorizontalCommand::PerformAction(Camera& target)
{

}

void MouseRotateVerticalCommand::PerformAction(Camera& target)
{

}