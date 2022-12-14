double2 getPointFromPixel(unsigned int width, unsigned int height, unsigned int x, unsigned int y, float xOffset, float yOffset, float zoom) {
	double aspectRatio = width / (double)(height);

	double xRatio = x / (double)(width) - 0.5;
	double yRatio = (height - y) / (double)(height) - 0.5;

	return (double2){xOffset + xRatio * 1 / zoom, yOffset + yRatio * (1 / zoom / aspectRatio)};
}

int2 getPixelFromPoint(unsigned int width, unsigned int height, double x, double y, float xOffset, float yOffset, float zoom) {
	double aspectRatio = width / (float)(height);

	x = ((x - xOffset) * zoom + 0.5) * width;
	y = height - ((y - yOffset) * zoom * aspectRatio + 0.5) * height;
	return (int2){(int)x, (int)y};
}

double dbl_abs(double d) {
	return d < 0 ? -d : d;
}

double2 square(double2 z) {
	return (double2){z.x * z.x - z.y * z.y, 2 * z.x * z.y};
}


double2 multiply(double2 a, double2 b) {
	return (double2){a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x};
}

double2 power(double2 z, unsigned int n)
{
	if (n == 0)
		return (double2){1, 0};
	double2 ret = z;
	for (int i = 0; i < n - 1; i++)
		ret = multiply(ret, z);
	return ret;
}

double2 divide(double2 a, double2 b) {
	return (double2)
	{
		(a.x * b.x + a.y * b.y) / (b.x * b.x + b.y * b.y),
		(a.y * b.x - a.x * b.y) / (b.x * b.x + b.y * b.y)
	};
}

double2 cube(double2 z) {
	return multiply(square(z), z);
}

double absolute(double2 z) {
	return sqrt(z.x * z.x + z.y * z.y);
}

float3 getColor(unsigned int iterations, int maxIterations, float3* colors, unsigned int nbColors) {
	double ratio = iterations / (double)maxIterations;
	float3 color = {0, 0, 0};
	double min = 0, max = 0;

	for (unsigned int i = 0; i < nbColors; i++)
	{
		min = i / (double)(nbColors);
		max = (i + 1) / (double)(nbColors);
		if (ratio >= min && ratio < max)
		{
			color = mix(colors[i], colors[i + 1], (float)((ratio - min) * nbColors));
			break;
		}
	}
	return color;
}
