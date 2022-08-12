#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ezgl
{
	class KeyListener
	{
	public:
		KeyListener();
		~KeyListener();
		virtual void onKeyPressed(int key, int scancode) = 0;
		virtual void onKeyReleased(int key, int scancode) = 0;
		virtual void onKeyRepeat(int key, int scancode) = 0;
		virtual void update(float deltaTime) = 0;

	protected:
		static std::vector<KeyListener*> _instances;

	public:
		friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void updateKeyListeners(float deltaTime);
	};

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void updateKeyListeners(float deltaTime);
}
