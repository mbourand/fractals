double2 getMinDistance(double2 z, float2* roots, unsigned int rootCount)
{
	double2 diff;
	double2 minDist = (double2){999999999999, -1};
	for (unsigned int i = 0; i < rootCount; i++)
	{
		double2 diff = {z.x - roots[i].x, z.y - roots[i].y};
		double dist = diff.x * diff.x + diff.y * diff.y;
		if (dist < minDist.x)
			minDist = (double2){dist, i};
	}
	return minDist;
}

float3 getNewtonColor(float3* colors, int iteration, double distance, int rootIndex, float tolerance)
{
	float smooth = (0.75 + 0.25 * cos(0.25 * (iteration - log2(log(distance) / log(tolerance)))));
	float3 asD3 = { smooth, smooth, smooth };
	return colors[rootIndex] * asD3;
}

__kernel void compute_fractal(unsigned int width, unsigned int height, float zoom, float xOffset, float yOffset, __global float *pixels, __global float3* colors, unsigned int nbColors, int maxIterations, float a, __global float2* roots)
{
	unsigned int x = get_global_id(0);
	unsigned int y = get_global_id(1);
	unsigned int pos = (y * width + x) * 3;

	double2 point = getPointFromPixel(width, height, x, y, xOffset, yOffset, zoom);

	double2 z = point;
	float3 color = {0, 0, 0};
	double tolerance = 0.0001;
	double2 minDist = -1;
	for (int i = 0; i < maxIterations; ++i)
	{
		z -= a * divide(cube(z) - (double2){1, 0}, 3 * square(z));
		minDist = getMinDistance(z, roots, 3);
		if (minDist.x < tolerance)
		{
			color = getNewtonColor(colors, i, minDist.x, minDist.y, tolerance);
			break;
		}
	}
	pixels[pos] = color.x;
	pixels[pos + 1] = color.y;
	pixels[pos + 2] = color.z;
}
