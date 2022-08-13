#pragma once

#include "Fractal.hpp"
#include "FractalController.hpp"
#include "EZGL/ComputeShader.h"

namespace frctl
{
	class Mandelbrot : public Fractal
	{
	protected:
		static constexpr int DEFAULT_MAX_ITERATIONS = 1000;
		static constexpr int DEFAULT_EXPONENT = 2;
		int _maxIterations;
		int _exponent;
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
