#include "Menu.hpp"
#include "EZGL/Window.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <algorithm>

namespace frctl
{
	Menu::Menu(const std::vector<Fractal*>& fractals)
		: _active(true), _requireUpdate(false), _displayedFractalId(0), _fractals(fractals)
	{
		for (Fractal* frac : _fractals)
			_names.push_back(frac->name.c_str());
	}

	void Menu::draw()
	{
		_fractals[_displayedFractalId]->draw();
		ImGui::Begin("Fractal Settings", &_active);
		auto currentFractal = _displayedFractalId;
		if (ImGui::Combo("Displayed Fractal", &_displayedFractalId, _names.data(), _names.size(), 3))
		{
			_fractals[currentFractal]->dispose();
			_requireUpdate = true;
		}
		ImGui::End();
	}

	void Menu::update() { _fractals[_displayedFractalId]->compute(); }

	bool Menu::requiresUpdate()
	{
		bool tmp = _requireUpdate;
		_requireUpdate = false;
		return tmp;
	}
}
