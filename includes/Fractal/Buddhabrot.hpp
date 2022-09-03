#pragma once

#include "Fractal.hpp"
#include "FractalController.hpp"
#include "EZGL/ComputeShader.h"

namespace frctl
{
	class Buddhabrot : public Fractal
	{
	protected:
		static constexpr int DEFAULT_MAX_ITERATIONS = 5000;
		static constexpr int DEFAULT_POINT_AMOUNT = 1000000;
		static constexpr double DEFAULT_BRIGHTNESS = 150;

		double _brightness;
		int _nbPoints;
		int _maxIterations;
		ezgl::ComputeShader _cs;

	private:
		void compute_partial(float zoom, float xOffset, float yOffset, std::vector<cl_double2>& points,
							 int color_channel, int maxIterations);
		bool preset(const std::string& buttonName, int maxIterations, int nbPoints, double brightness);

	public:
		Buddhabrot(std::vector<float>& pixels);
		Buddhabrot(const Buddhabrot& other);
		Buddhabrot& operator=(const Buddhabrot& other);

		FractalController init();
		void compute(float zoom, float xOffset, float yOffset);
		void draw();
	};
}
