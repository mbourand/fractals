#pragma once

#include "KeyListener.h"
#include "MouseListener.h"
#include "PerspectiveCamera.h"
#include <map>

namespace ezgl
{
	class FlyController : public KeyListener, public MouseListener
	{
	protected:
		bool _forwardPressed, _backwardPressed, _leftPressed, _rightPressed, _upPressed, _downPressed;
		std::map<int, bool*> _keys;

		bool _focused;

	public:
		PerspectiveCamera& camera;
		float verticalSpeed;
		float horizontalSpeed;
		float mouseSensivity;

		FlyController(PerspectiveCamera& camera);

		virtual void onKeyPressed(int key, int scancode) override;
		virtual void onKeyReleased(int key, int scancode) override;
		virtual void onKeyRepeat(int key, int scancode) override;

		virtual void update(float deltaTime) override;

		virtual void onMouseMoved(double x, double y) override;
		virtual void onMouseScroll(double xoffset, double yoffset) override;
		virtual void onMouseEntered(int entered) override;
		virtual void onMouseButtonPressed(int button, int mods) override;
		virtual void onMouseButtonReleased(int button, int mods) override;

	};
}
