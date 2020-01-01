#pragma once

#include "KeyCommand.h"

#include <string>


#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Window
{
private:
	unsigned int m_Height, m_Width; // Size of the window
	std::string m_Title; // Title of the window
	bool windowStatus = false; // Control window shutdown ( true -> close the window )
	GLFWwindow* m_SharedWindow; 	
	GLFWmonitor* m_Monitor;
	unsigned int m_SwapInterval = 1; // Swap interval to regulate control time
private:
	Key* k_W;
	Key* k_S;
	Key* k_A;
	Key* k_D;
private:
	Camera* mainCamera;
	GLFWwindow* m_GLWindow; // MainWindow
public:
	Window(unsigned int p_Height = 640, unsigned int p_Width = 480, std::string p_Title = "", Camera* p_Camera = nullptr,
		   GLFWmonitor* p_Monitor = nullptr, GLFWwindow* p_SharedWindow = nullptr);
	~Window();

	void Refresh();
	void MakeCurrentContext();
	void CreateEventCallbacks();
public:
	void SetWindowStatus(bool newStatus);
public:
	inline bool GetWindowStatus() const { return windowStatus; }
	inline unsigned int GetHeight() const { return m_Height; }
	inline unsigned int GetWidth() const { return m_Width; }
	inline std::string GetTitle() const { return m_Title; }
	inline GLFWwindow* GetWindow() { return m_GLWindow; }
	inline Camera* GetMainCamera() { return mainCamera; }

	inline Key* GetWKey() { return k_W; }
	inline Key* GetSKey() { return k_S; }
	inline Key* GetAKey() { return k_A; }
	inline Key* GetDKey() { return k_D; }
	
public:
	static void OnKeyPress(GLFWwindow* targetWindow, int keyCode, int code, int action, int mode);
	static void OnMouseTurn(GLFWwindow* targetWindow, double mouseX, double mouseY);
};