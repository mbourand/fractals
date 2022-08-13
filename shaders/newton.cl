int converged(double2 z, double tolerance, double2* roots, unsigned int rootCount)
{
	double2 diff;
	for (unsigned int i = 0; i < rootCount; i++)
	{
		double2 diff = z - roots[i];
		if (dbl_abs(diff.x) < tolerance && dbl_abs(diff.y) < tolerance)
			return i;
	}
	return -1;
}

__kernel void compute_fractal(unsigned int width, unsigned int height, float zoom, float xOffset, float yOffset, __global unsigned char *pixels, __global float3* colors, unsigned int nbColors, int maxIterations, float a)
{
	double2 roots[3] =
	{
		(double2){1, 0},
		(double2){-.5, 0.86602},
		(double2){-.5, -0.86602}
	};

	float3 rootColors[3] =
	{
		(float3){1, 0, 0},
		(float3){0, 1, 0},
		(float3){0, 0, 1}
	};

	unsigned int x = get_global_id(0);
	unsigned int y = get_global_id(1);
	unsigned int pos = (y * width + x) * 3;

	double2 point = getPointFromPixel(width, height, x, y, xOffset, yOffset, zoom);

	double2 z = point;
	float3 color = {0, 0, 0};
	double tolerance = 0.001;
	int convergedRoot = -1;
	for (int i = 0; i < maxIterations; ++i)
	{
		z -= a * divide(cube(z) - (double2){1, 0}, 3 * square(z));
		convergedRoot = converged(z, tolerance, roots, 3);
		if (convergedRoot != -1)
		{
			color = rootColors[convergedRoot];
			break;
		}
	}
	pixels[pos] = color.x * 255;
	pixels[pos + 1] = color.y * 255;
	pixels[pos + 2] = color.z * 255;
}
