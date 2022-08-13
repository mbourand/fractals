#pragma once

#include "Fractal.hpp"
#include "FractalController.hpp"
#include "EZGL/ComputeShader.h"

namespace frctl
{
	class Newton : public Fractal
	{
	protected:
		int _maxIterations;
		ezgl::ComputeShader _cs;
		float _a;

	public:
		Newton(std::vector<uint8_t>& pixels);
		Newton(const Newton& other);
		Newton& operator=(const Newton& other);

		FractalController init();
		void compute(float zoom, float xOffset, float yOffset);
		void draw();
	};
}
