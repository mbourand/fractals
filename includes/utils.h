#pragma once

#include <map>

namespace frctl
{
	std::pair<double, double> screenToFractal(double x, double y, double zoom, double width, double height,
											  double xOffset, double yOffset);
	std::pair<double, double> fractalToScreen(unsigned int width, unsigned int height, double x, double y,
											  float xOffset, float yOffset, float zoom);
	double randomDouble(double min, double max);
}
