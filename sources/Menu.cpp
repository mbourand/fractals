#include "Menu.hpp"
#include "EZGL/Window.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <algorithm>

namespace frctl
{
	Menu::Menu(const std::vector<Fractal*>& fractals) : _displayedFractalId(0), _fractals(fractals)
	{
		for (Fractal* frac : _fractals)
			_names.push_back(frac->name.c_str());
	}

	bool Menu::update()
	{
		bool changed = false;
		ImGui::Begin("Fractal Settings");
		auto currentFractal = _displayedFractalId;
		if (ImGui::Combo("Displayed Fractal", &_displayedFractalId, _names.data(), _names.size()))
		{
			changed = true;
			getSelectedFractal()->requireUpdate = true;
		}
		ImGui::End();
		return changed;
	}

	Fractal* Menu::getSelectedFractal() const { return _fractals[_displayedFractalId]; }
}
