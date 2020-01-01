
#include "Window.h"
#include "Camera.h"
#include "Renderer.h"
#include <iostream>

Window::Window(unsigned int p_Height, unsigned int p_Width, std::string p_Title, Camera* p_Camera,
	GLFWmonitor* p_Monitor, GLFWwindow* p_SharedWindow)
	:	m_Height(p_Height), m_Width(p_Width), m_Title(p_Title), mainCamera(p_Camera), m_Monitor(p_Monitor), m_SharedWindow(p_SharedWindow),
		k_W(nullptr), k_S(nullptr), k_A(nullptr), k_D(nullptr)
{
	k_W = new Key(GLFW_KEY_W, new GoForwardCommand());
	k_S = new Key(GLFW_KEY_S, new GoBackwardCommand());
	k_D = new Key(GLFW_KEY_D, new GoRightCommand());
	k_A = new Key(GLFW_KEY_A, new GoLeftCommand());

	if (!glfwInit())
		std::cout << "Error\n";

	m_GLWindow = glfwCreateWindow(m_Height, m_Width, m_Title.c_str(), m_Monitor, m_SharedWindow);
	
	glfwMakeContextCurrent(m_GLWindow);
	
	if (glewInit() != GLEW_OK)
		std::cout << "Error!";
	GLCALL(glEnable(GL_DEPTH_TEST));

	glfwSetWindowUserPointer(m_GLWindow, this);

	CreateEventCallbacks();
}

Window::~Window()
{
	// TODO
}

void Window::CreateEventCallbacks()
{
	glfwSetKeyCallback(m_GLWindow, OnKeyPress);
	glfwSetCursorPosCallback(m_GLWindow, OnMouseTurn);
}

void Window::OnKeyPress(GLFWwindow* targetWindow, int keyCode, int code, int action, int mode)
{
	Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(targetWindow));

	if (action == GLFW_REPEAT)
	{
		switch (keyCode)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(targetWindow, true);
			break;
		case GLFW_KEY_W:
			currentWindow->GetWKey()->Perform(*(currentWindow->GetMainCamera()));
			currentWindow->GetWKey()->SetPressed(true);
			break;
		case GLFW_KEY_S:
			currentWindow->GetSKey()->Perform(*(currentWindow->GetMainCamera()));
			currentWindow->GetSKey()->SetPressed(true);
			break;
		case GLFW_KEY_A:
			currentWindow->GetAKey()->Perform(*(currentWindow->GetMainCamera()));
			currentWindow->GetAKey()->SetPressed(true);
			break;
		case GLFW_KEY_D:
			currentWindow->GetDKey()->Perform(*(currentWindow->GetMainCamera()));
			currentWindow->GetDKey()->SetPressed(true);
			break;
		default: break;
		}
	}

	else if (action == GLFW_RELEASE) 
	{
		switch (keyCode)
		{
		case GLFW_KEY_W:
			currentWindow->GetWKey()->SetPressed(false);
			break;
		case GLFW_KEY_S:
			currentWindow->GetSKey()->SetPressed(false);
			break;
		case GLFW_KEY_A:
			currentWindow->GetAKey()->SetPressed(false);
			break;
		case GLFW_KEY_D:
			currentWindow->GetDKey()->SetPressed(false);
			break;
		default: break;
		}
	}
}

void Window::OnMouseTurn(GLFWwindow* targetWindow, double mouseX, double mouseY)
{
	//std::cout << "Turned";
	Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(targetWindow));

	currentWindow->GetMainCamera()->Update(mouseX, mouseY);
}

void Window::MakeCurrentContext() 
{ 
	//glfwSwapInterval(m_SwapInterval);
	glfwMakeContextCurrent(m_GLWindow); 
}

// Setters
void Window::SetWindowStatus(bool newStatus) { windowStatus = newStatus; }

// Main loop
void Window::Refresh()
{
	glfwSwapBuffers(m_GLWindow);
	glfwPollEvents();
}