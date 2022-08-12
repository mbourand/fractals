#include "EZGL/KeyListener.h"
#include <algorithm>

namespace ezgl
{
	std::vector<KeyListener*> KeyListener::_instances;

	KeyListener::KeyListener()
	{
		_instances.push_back(this);
	}

	KeyListener::~KeyListener()
	{
		static_cast<void>(std::remove_if(_instances.begin(), _instances.end(), [this](KeyListener* a) -> bool { return a == this; }));
	}


	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		for (auto& instance : KeyListener::_instances)
		{
			switch (action)
			{
			case GLFW_PRESS:
				instance->onKeyPressed(key, scancode);
				break;
			case GLFW_RELEASE:
				instance->onKeyReleased(key, scancode);
				break;
			case GLFW_REPEAT:
				instance->onKeyRepeat(key, scancode);
				break;
			}
		}
	}

	void updateKeyListeners(float deltaTime)
	{
		for (auto& instance : KeyListener::_instances)
			instance->update(deltaTime);
	}
}
