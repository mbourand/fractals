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

__kernel void compute_fractal(unsigned int width, unsigned int height, float zoom, float xOffset, float yOffset, __global unsigned char *pixels, __global float3* colors, unsigned int nbColors, int maxIterations, float2 c)
{
	unsigned int x = get_global_id(0);
	unsigned int y = get_global_id(1);
	unsigned int pos = (y * width + x) * 3;

	double aspectRatio = width / (double)(height);

	double xRatio = x / (double)(width) - 0.5;
	double yRatio = (height - y) / (double)(height) - 0.5;

	double pointX = xOffset + xRatio * 1 / zoom;
	double pointY = yOffset + yRatio * (1 / zoom / aspectRatio);

	double2 z = {pointX, pointY};
	for (int i = 0; i < maxIterations; ++i)
	{
		double tmp = z.x * z.x - z.y * z.y + c.x;
		z.y = 2 * z.x * z.y + c.y;
		z.x = tmp;
		if (z.y * z.y + z.x * z.x > 4)
		{
			float3 color = getColor(i, maxIterations / 10, colors, nbColors);
			pixels[pos] = color.x * 255;
			pixels[pos + 1] = color.y * 255;
			pixels[pos + 2] = color.z * 255;
			return;
		}
	}
	pixels[pos] = 0;
	pixels[pos + 1] = 0;
	pixels[pos + 2] = 0;
}
