#pragma once

#include "Fractal.hpp"
#include "FractalController.hpp"
#include "EZGL/ComputeShader.h"

namespace frctl
{
	class Newton : public Fractal
	{
	protected:
		static constexpr int DEFAULT_MAX_ITERATIONS = 400;
		static constexpr float DEFAULT_A = 1;
		int _maxIterations;
		ezgl::ComputeShader _cs;
		float _a;
		std::vector<cl_float2> _points;

	public:
		Newton(std::vector<uint8_t>& pixels);
		Newton(const Newton& other);
		Newton& operator=(const Newton& other);

		FractalController init();
		void compute(float zoom, float xOffset, float yOffset);
		void draw();
	};
}
