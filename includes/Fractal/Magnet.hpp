#pragma once

#include "Fractal.hpp"
#include "FractalController.hpp"
#include "EZGL/ComputeShader.h"

namespace frctl
{
	class Magnet : public Fractal
	{
	protected:
		static constexpr int DEFAULT_MAX_ITERATIONS = 1000;
		static constexpr cl_float2 DEFAULT_C = {-0.67, 0.209};
		int _maxIterations;
		cl_float2 _c;
		ezgl::ComputeShader _cs;

	public:
		Magnet(std::vector<uint8_t>& pixels);
		Magnet(const Magnet& other);
		Magnet& operator=(const Magnet& other);

		FractalController init();
		void compute(float zoom, float xOffset, float yOffset);
		void draw();
	};
}
