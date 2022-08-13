#pragma once

#include "Fractal.hpp"
#include "FractalController.hpp"
#include "EZGL/ComputeShader.h"

namespace frctl
{
	class Julia : public Fractal
	{
	protected:
		int _maxIterations;
		cl_float2 _c;
		ezgl::ComputeShader _cs;

	public:
		Julia(std::vector<uint8_t>& pixels);
		Julia(const Julia& other);
		Julia& operator=(const Julia& other);

		FractalController init();
		void compute(float zoom, float xOffset, float yOffset);
		void draw();
	};
}
