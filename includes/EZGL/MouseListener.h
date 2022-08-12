#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ezgl
{
	class MouseListener
	{
	public:
		MouseListener();
		~MouseListener();
		virtual void onMouseMoved(double x, double y) = 0;
		virtual void onMouseEntered(int entered) = 0;
		virtual void onMouseButtonPressed(int button, int mods) = 0;
		virtual void onMouseButtonReleased(int button, int mods) = 0;
		virtual void onMouseScroll(double xoffset, double yoffset) = 0;
		virtual void update(float deltaTime) = 0;

	protected:
		static std::vector<MouseListener*> _instances;

	public:
		friend void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		friend void mousePosCallback(GLFWwindow* window, double x, double y);
		friend void mouseEnterCallback(GLFWwindow* window, int entered);
		friend void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		friend void updateMouseListeners(float deltaTime);
	};

	void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void mousePosCallback(GLFWwindow* window, double x, double y);
	void mouseEnterCallback(GLFWwindow* window, int entered);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void updateMouseListeners(float deltaTime);
}
