__kernel void compute_fractal(unsigned int width, unsigned int height, float zoom, float xOffset, float yOffset, __global float *pixels, __global double2* points, int maxIterations, float brightness)
{
	unsigned int pos = get_global_id(0);
	double2 point = points[pos];
	
	double2 z = {0, 0};
	float3 color = {0, 0, 0};

	int i = 0;
	for (; i < maxIterations && z.y * z.y + z.x * z.x < 4; ++i)
		z = square(z) + point;

	double logMax = log((double)maxIterations);
	if (i < maxIterations - 3)
	{
		i = 0;
		z = (double2){0, 0};
		for (; i < maxIterations && z.y * z.y + z.x * z.x < 4; ++i)
		{
			z = square(z) + point;
			if (i < 3)
				continue;
			int2 pixel = getPixelFromPoint(width, height, z.x, z.y, xOffset, yOffset, zoom);
			if (pixel.x < 0 || pixel.y < 0 || pixel.x >= width || pixel.y >= height)
				continue;
			unsigned int pixelIndex = pixel.y * width + pixel.x;
			pixels[pixelIndex] = min(pixels[pixelIndex] + (brightness / 100.0f), 1.0f);
		}
	}
}
