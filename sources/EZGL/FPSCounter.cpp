#include "EZGL/FPSCounter.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>

namespace ezgl
{
	FPSCounter::FPSCounter()
	{
		this->_fps = 0;
		this->_frameCount = 0;
		this->_lastTime = 0;
	}

	void FPSCounter::update()
	{
		this->_frameCount++;

		int currentTime = glfwGetTime();
		if (currentTime - this->_lastTime >= 1.0)
		{
			this->_fps = this->_frameCount;
			this->_frameCount = 0;
		}

		this->_lastTime = currentTime;
	}

	int FPSCounter::getFPS() { return this->_fps; }
}
