#pragma once

#include "Fractal.hpp"

namespace frctl
{
	class Menu
	{
	protected:
		bool _active = true;
		bool _requireUpdate = false;
		int _displayedFractalId = 0;
		std::vector<Fractal*> _fractals;
		std::vector<const char*> _names;

	public:
		Menu() = default;
		Menu(const Menu& other) = default;
		Menu(const std::vector<Fractal*>& fractals);
		Menu& operator=(const Menu& other) = default;

		bool requiresUpdate();

		void draw();
		void update();
	};
}
