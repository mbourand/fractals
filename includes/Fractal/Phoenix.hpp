#pragma once

#include "Fractal.hpp"
#include "FractalController.hpp"
#include "EZGL/ComputeShader.h"

namespace frctl
{
	class Phoenix : public Fractal
	{
	protected:
		static constexpr int DEFAULT_MAX_ITERATIONS = 1200;
		static constexpr cl_float2 DEFAULT_C = {0.5667, 0};
		static constexpr cl_float2 DEFAULT_P = {-0.5, 0};

		int _maxIterations;
		cl_float2 _c;
		cl_float2 _p;
		ezgl::ComputeShader _cs;

	public:
		Phoenix(std::vector<float>& pixels);
		Phoenix(const Phoenix& other);
		Phoenix& operator=(const Phoenix& other);

		FractalController init();
		void compute(float zoom, float xOffset, float yOffset);
		void draw();
	};
}
