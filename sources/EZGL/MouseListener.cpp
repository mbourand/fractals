#include "EZGL/MouseListener.h"
#include <algorithm>
#include <iostream>

namespace ezgl
{
	std::vector<MouseListener*> MouseListener::_instances;

	MouseListener::MouseListener() { _instances.push_back(this); }

	MouseListener::~MouseListener()
	{
		for (auto it = MouseListener::_instances.begin(); it != MouseListener::_instances.end(); ++it)
		{
			if (this == *it)
			{
				MouseListener::_instances.erase(it);
				break;
			}
		}
	}

	MouseListener::MouseListener(const MouseListener& other) { _instances.push_back(this); }

	void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		for (auto& instance : MouseListener::_instances)
			instance->onMouseScroll(xoffset, yoffset);
	}

	void mousePosCallback(GLFWwindow* window, double x, double y)
	{
		for (auto& instance : MouseListener::_instances)
			instance->onMouseMoved(x, y);
	}

	void mouseEnterCallback(GLFWwindow* window, int entered)
	{
		for (auto& instance : MouseListener::_instances)
			instance->onMouseEntered(entered);
	}

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		for (auto& instance : MouseListener::_instances)
		{
			switch (action)
			{
				case GLFW_PRESS:
					instance->onMouseButtonPressed(button, mods);
					break;
				case GLFW_RELEASE:
					instance->onMouseButtonReleased(button, mods);
					break;
			}
		}
	}

	void updateMouseListeners(float deltaTime)
	{
		for (auto& instance : MouseListener::_instances)
			instance->update(deltaTime);
	}
}
