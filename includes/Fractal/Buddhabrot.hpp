#pragma once

#include "Fractal.hpp"
#include "FractalController.hpp"
#include "EZGL/ComputeShader.h"

namespace frctl
{
	class Buddhabrot : public Fractal
	{
	protected:
		static constexpr int DEFAULT_MAX_ITERATIONS = 1700;
		static constexpr int DEFAULT_POINT_AMOUNT = 900000;
		static constexpr float DEFAULT_BRIGHTNESS = 3.5;

		float _brightness;
		int _nbPoints;
		int _maxIterations;
		ezgl::ComputeShader _cs;

	private:
		void compute_partial(float zoom, float xOffset, float yOffset, std::vector<cl_double2>& points,
							 int color_channel, int maxIterations);

	public:
		Buddhabrot(std::vector<uint8_t>& pixels);
		Buddhabrot(const Buddhabrot& other);
		Buddhabrot& operator=(const Buddhabrot& other);

		FractalController init();
		void compute(float zoom, float xOffset, float yOffset);
		void draw();
	};
}
