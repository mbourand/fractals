#pragma once

#include "EZGL/MouseListener.h"

namespace frctl
{
	class Fractal;

	class FractalController : public ezgl::MouseListener
	{
	protected:
		bool _grabbing;
		double _mouseX;
		double _mouseY;

	public:
		float zoom;
		float xOffset;
		float yOffset;
		Fractal* fractal;

		FractalController() = default;
		FractalController(const FractalController& other) = default;
		FractalController& operator=(const FractalController& other) = default;
		FractalController(Fractal* fractal, float zoom, float xOffset, float yOffset);

		void onMouseMoved(double x, double y);
		void onMouseEntered(int entered);
		void onMouseButtonPressed(int button, int mods);
		void onMouseButtonReleased(int button, int mods);
		void onMouseScroll(double xoffset, double yoffset);
		void update(float deltaTime);
	};
}
