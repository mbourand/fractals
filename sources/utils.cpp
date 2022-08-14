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

	std::pair<double, double> fractalToScreen(unsigned int width, unsigned int height, double x, double y,
											  float xOffset, float yOffset, float zoom)
	{
		double aspectRatio = width / (float)(height);

		x = ((x - xOffset) * zoom + 0.5) * width;
		y = height - ((y - yOffset) * zoom * aspectRatio + 0.5) * height;
		return std::make_pair(x, y);
	}

	double randomDouble(double min, double max) { return rand() / (double)RAND_MAX * (max - min) + min; }
}
