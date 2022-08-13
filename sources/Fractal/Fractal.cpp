#include "Fractal.hpp"
#include "FractalController.hpp"

namespace frctl
{
	Fractal::Fractal(const std::string& name, std::vector<uint8_t>& pixels)
		: name(name), pixels(pixels), requireUpdate(true)
	{
	}

	Fractal& Fractal::operator=(const Fractal& other)
	{
		name = other.name;
		fbo = other.fbo;
		pixels = other.pixels;
		texture = other.texture;
		requireUpdate = other.requireUpdate;
		return *this;
	}

}
