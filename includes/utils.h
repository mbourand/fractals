#pragma once

#include <map>

namespace frctl
{
	std::pair<double, double> screenToFractal(double x, double y, double zoom, double width, double height,
											  double xOffset, double yOffset);
}
