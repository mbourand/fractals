#include "utils.h"

namespace frctl
{
	std::pair<double, double> screenToFractal(double x, double y, double zoom, double width, double height,
											  double xOffset = 0, double yOffset = 0)
	{
		double aspectRatio = width / (float)(height);

		double xRatio = x / (float)(width)-0.5;
		double yRatio = (height - y) / (float)(height)-0.5;

		double pointX = xOffset + xRatio * 1 / zoom;
		double pointY = yOffset + yRatio * (1 / zoom / aspectRatio);

		return std::make_pair(pointX, pointY);
	}
}
