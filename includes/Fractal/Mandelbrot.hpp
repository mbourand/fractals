#pragma once

#include "Fractal.hpp"
#include "FractalController.hpp"
#include "EZGL/ComputeShader.h"

namespace frctl
{
	class Mandelbrot : public Fractal
	{
	protected:
		bool _requireUpdate;
		ezgl::Texture _texture;

	public:
		int maxIterations;
		ezgl::ComputeShader cs;
		std::vector<uint8_t> pixels;
		FractalController controller;

		Mandelbrot();
		Mandelbrot(const Mandelbrot& other);
		Mandelbrot& operator=(const Mandelbrot& other);

		void compute();
		void draw();
		void dispose();
	};
}
