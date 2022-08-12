#include "EZGL/FlyController.h"
#include "EZGL/Window.h"

namespace ezgl
{
	FlyController::FlyController(PerspectiveCamera& camera)
		: camera(camera), _forwardPressed(false), _backwardPressed(false), _leftPressed(false),
		_rightPressed(false), _upPressed(false), _downPressed(false), _focused(false)
	{
		this->horizontalSpeed = 8.0f;
		this->verticalSpeed = 7.0f;
		this->mouseSensivity = 0.2f;

		this->_keys[GLFW_KEY_W] = &(this->_forwardPressed);
		this->_keys[GLFW_KEY_S] = &(this->_backwardPressed);
		this->_keys[GLFW_KEY_A] = &(this->_leftPressed);
		this->_keys[GLFW_KEY_D] = &(this->_rightPressed);
		this->_keys[GLFW_KEY_SPACE] = &(this->_upPressed);
		this->_keys[GLFW_KEY_LEFT_CONTROL] = &(this->_downPressed);
	}

	void FlyController::onKeyPressed(int key, int scancode)
	{
		auto it = this->_keys.find(key);
		if (it != this->_keys.end())
			*(it->second) = true;

		if (key == GLFW_KEY_ESCAPE)
		{
			ezgl::Window::showCursor();
			this->_focused = false;
		}

		if (key == GLFW_KEY_E)
		{
			this->verticalSpeed += 3.0f;
			this->horizontalSpeed += 3.0f;
		}

		if (key == GLFW_KEY_Q)
		{
			this->verticalSpeed = std::max(0.0f, this->verticalSpeed - 3.0f);
			this->horizontalSpeed = std::max(0.0f, this->horizontalSpeed - 3.0f);
		}
	}

	void FlyController::onKeyReleased(int key, int scancode)
	{
		auto it = this->_keys.find(key);
		if (it != this->_keys.end())
			*(it->second) = false;
	}

	void FlyController::onKeyRepeat(int key, int scancode) {}

	void FlyController::onMouseMoved(double x, double y)
	{
		if (!this->_focused)
			return;

		camera.rotate((x - ezgl::Window::getWidth() / 2) * mouseSensivity, -(y - ezgl::Window::getHeight() / 2) * mouseSensivity);

		ezgl::Window::centerCursor();
	}

	void FlyController::onMouseEntered(int entered) {}
	void FlyController::onMouseButtonReleased(int button, int mods) {}
	void FlyController::onMouseScroll(double xoffset, double yoffset) {}

	void FlyController::onMouseButtonPressed(int button, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			ezgl::Window::hideCursor();
			ezgl::Window::centerCursor();
			this->_focused = true;
		}
	}

	void FlyController::update(float deltaTime)
	{
		if (this->_rightPressed - this->_leftPressed == 0 && this->_upPressed - this->_downPressed == 0 && this->_forwardPressed - this->_backwardPressed == 0)
			return;

		Vector3<float> dir(0, 0, 0);

		Vector3<float> worldUp(0, 1, 0);
		Vector3<float> horizontal(1, 0, 1);
		
		Vector3<float> left = camera.getDirection().cross(worldUp).normalize();

		dir += left * (this->_rightPressed - this->_leftPressed);
		dir += worldUp * (this->_upPressed - this->_downPressed);
		dir += camera.getDirection() * horizontal * (this->_forwardPressed - this->_backwardPressed);

		camera.move(dir.normalize() * Vector3<float>(horizontalSpeed * deltaTime, verticalSpeed * deltaTime, horizontalSpeed * deltaTime));
	}
}
