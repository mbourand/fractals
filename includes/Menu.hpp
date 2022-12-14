#pragma once

#include "Fractal.hpp"

namespace frctl
{
	class Menu
	{
	protected:
		int _displayedFractalId = 0;
		std::vector<Fractal*> _fractals;
		std::vector<const char*> _names;

	public:
		Menu() = default;
		Menu(const Menu& other) = default;
		Menu(const std::vector<Fractal*>& fractals);
		Menu& operator=(const Menu& other) = default;

		bool requiresUpdate();

		bool update();
		Fractal* getSelectedFractal() const;
	};
}
