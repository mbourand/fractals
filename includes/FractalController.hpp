#pragma once

#include "EZGL/MouseListener.h"

namespace frctl
{
	class FractalController : public ezgl::MouseListener
	{
	protected:
		bool _requireUpdate;
		bool _grabbing;
		double _mouseX;
		double _mouseY;

	public:
		float zoom;
		float xOffset;
		float yOffset;

		FractalController() = default;
		FractalController(const FractalController& other) = default;
		FractalController& operator=(const FractalController& other) = default;
		FractalController(float zoom, float xOffset, float yOffset);

		inline bool requiresUpdate()
		{
			bool tmp = _requireUpdate;
			_requireUpdate = false;
			return tmp;
		}

		void onMouseMoved(double x, double y);
		void onMouseEntered(int entered);
		void onMouseButtonPressed(int button, int mods);
		void onMouseButtonReleased(int button, int mods);
		void onMouseScroll(double xoffset, double yoffset);
		void update(float deltaTime);
	};
}
