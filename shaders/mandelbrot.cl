__kernel void compute_fractal(unsigned int width, unsigned int height, float zoom, float xOffset, float yOffset, __global unsigned char *pixels, __global float3* colors, unsigned int nbColors, int maxIterations)
{
	unsigned int x = get_global_id(0);
	unsigned int y = get_global_id(1);
	unsigned int pos = (y * width + x) * 3;

	double2 point = getPointFromPixel(width, height, x, y, xOffset, yOffset, zoom);

	double2 z = {0, 0};
	float3 color = {0, 0, 0};
	for (int i = 0; i < maxIterations; ++i)
	{
		z = square(z) + point;
		if (z.y * z.y + z.x * z.x > 4)
		{
			color = getColor(i, maxIterations / 10, colors, nbColors);
			break;
		}
	}
	pixels[pos] = color.x * 255;
	pixels[pos + 1] = color.y * 255;
	pixels[pos + 2] = color.z * 255;
}
