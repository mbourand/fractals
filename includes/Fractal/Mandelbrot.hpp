#pragma once

#include "Fractal.hpp"
#include "FractalController.hpp"
#include "EZGL/ComputeShader.h"

namespace frctl
{
	class Mandelbrot : public Fractal
	{
	protected:
		int _maxIterations;
		ezgl::ComputeShader _cs;

	public:
		Mandelbrot(std::vector<uint8_t>& pixels);
		Mandelbrot(const Mandelbrot& other);
		Mandelbrot& operator=(const Mandelbrot& other);

		FractalController init();
		void compute(float zoom, float xOffset, float yOffset);
		void draw();
	};
}
