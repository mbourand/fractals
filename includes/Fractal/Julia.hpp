#pragma once

#include "Fractal.hpp"
#include "FractalController.hpp"
#include "EZGL/ComputeShader.h"

namespace frctl
{
	class Julia : public Fractal
	{
	protected:
		bool _requireUpdate;
		ezgl::Texture _texture;

	public:
		int maxIterations;
		cl_float2 c;
		ezgl::ComputeShader cs;
		std::vector<uint8_t> pixels;
		FractalController controller;

		Julia();
		Julia(const Julia& other);
		Julia& operator=(const Julia& other);

		void compute();
		void draw();
		void dispose();
	};
}
