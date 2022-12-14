#include "FractalController.hpp"
#include "Fractal.hpp"
#include "utils.h"
#include "EZGL/Window.h"
#include <iostream>
#include <algorithm>

namespace frctl
{
	FractalController::FractalController(Fractal* fractal, float zoom, float xOffset, float yOffset, bool enable)
		: zoom(zoom), fractal(fractal), _grabbing(false), xOffset(xOffset), yOffset(yOffset), enable(enable)
	{
	}

	FractalController& FractalController::operator=(const FractalController& other)
	{
		zoom = other.zoom;
		fractal = other.fractal;
		xOffset = other.xOffset;
		yOffset = other.yOffset;
		enable = other.enable;
		return *this;
	}

	void FractalController::onMouseMoved(double x, double y)
	{
		if (!enable)
			return;
		if (_grabbing)
		{
			auto posInFractal = frctl::screenToFractal(_mouseX, _mouseY, zoom, ezgl::Window::getWidth(),
													   ezgl::Window::getHeight(), xOffset, yOffset);
			auto newPosInFractal = frctl::screenToFractal(x, y, zoom, ezgl::Window::getWidth(),
														  ezgl::Window::getHeight(), xOffset, yOffset);
			xOffset -= newPosInFractal.first - posInFractal.first;
			yOffset += newPosInFractal.second - posInFractal.second;
			fractal->requireUpdate = true;
		}

		_mouseX = x;
		_mouseY = y;
	}

	void FractalController::onMouseEntered(int entered) {}
	void FractalController::onMouseButtonPressed(int button, int mods)
	{
		if (!enable || ezgl::Window::mouseIsOnImGuiElement())
			return;
		if (button == GLFW_MOUSE_BUTTON_1)
			_grabbing = true;
	}
	void FractalController::onMouseButtonReleased(int button, int mods)
	{
		if (!enable || button == GLFW_MOUSE_BUTTON_1)
			_grabbing = false;
	}

	void FractalController::onMouseScroll(double xoffset, double yoffset)
	{
		if (!enable || ezgl::Window::mouseIsOnImGuiElement() || _grabbing)
			return;

		auto mousePos = frctl::screenToFractal(_mouseX, _mouseY, zoom, ezgl::Window::getWidth(),
											   ezgl::Window::getHeight(), xOffset, yOffset);
		zoom *= (yoffset > 0 ? 1.1 : 1 / 1.1);
		zoom = std::max(0.01f, zoom);
		auto newMousePos = frctl::screenToFractal(_mouseX, _mouseY, zoom, ezgl::Window::getWidth(),
												  ezgl::Window::getHeight(), xOffset, yOffset);

		xOffset -= (newMousePos.first - mousePos.first) * (yoffset > 0 ? 1 : -1);
		yOffset -= (newMousePos.second - mousePos.second) * (yoffset > 0 ? -1 : 1);

		fractal->requireUpdate = true;
	}

	void FractalController::update(float deltaTime) {}
}
