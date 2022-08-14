#include "Buddhabrot.hpp"
#include "myimgui.h"
#include "utils.h"
#include <CL/cl.hpp>
#include "EZGL/Window.h"

namespace frctl
{
	Buddhabrot::Buddhabrot(std::vector<uint8_t>& pixels)
		: Fractal("Buddhabrot", pixels), _maxIterations(Buddhabrot::DEFAULT_MAX_ITERATIONS),
		  _nbPoints(Buddhabrot::DEFAULT_POINT_AMOUNT), _brightness(Buddhabrot::DEFAULT_BRIGHTNESS)
	{
		_cs = ezgl::ComputeShader({"../../shaders/utils.cl", "../../shaders/buddhabrot.cl"}, "compute_fractal");
	}

	Buddhabrot::Buddhabrot(const Buddhabrot& other) : Fractal(other.name, other.pixels) { *this = other; }
	Buddhabrot& Buddhabrot::operator=(const Buddhabrot& other)
	{
		Fractal::operator=(other);
		_nbPoints = other._nbPoints;
		_brightness = other._brightness;
		_maxIterations = other._maxIterations;
		_cs = other._cs;
		return *this;
	}

	FractalController Buddhabrot::init()
	{
		_nbPoints = Buddhabrot::DEFAULT_POINT_AMOUNT;
		_brightness = Buddhabrot::DEFAULT_BRIGHTNESS;
		_maxIterations = Buddhabrot::DEFAULT_MAX_ITERATIONS;
		return FractalController(this, 0.2, -0.5, 0);
	}

	void Buddhabrot::compute_partial(float zoom, float xOffset, float yOffset, std::vector<cl_double2>& points,
									 int color_channel, int maxIterations)
	{
		unsigned int width = ezgl::Window::getWidth();
		unsigned int height = ezgl::Window::getHeight();

		std::vector<float> pixelsFloat(width * height, 0);

		cl::Buffer pixelsBuffer = _cs.createBuffer(CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, pixelsFloat);
		cl::Buffer pointsBuffer = _cs.createBuffer(CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, points);

		_cs.setArg(0, width);
		_cs.setArg(1, height);
		_cs.setArg(2, zoom);
		_cs.setArg(3, xOffset);
		_cs.setArg(4, yOffset);
		_cs.setArg(5, pixelsBuffer);
		_cs.setArg(6, pointsBuffer);
		_cs.setArg(7, maxIterations);
		_cs.setArg(8, _brightness);
		_cs.run(cl::NDRange(points.size()));

		_cs.commands.enqueueReadBuffer(pixelsBuffer, CL_TRUE, 0, pixelsFloat.size() * sizeof(float),
									   pixelsFloat.data());
		for (int i = 0; i < pixelsFloat.size(); i++)
			pixels[i * 3 + color_channel] = pixelsFloat[i] * 255;
	}

	void Buddhabrot::compute(float zoom, float xOffset, float yOffset)
	{
		if (!requireUpdate)
			return;

		pixels.assign(ezgl::Window::getWidth() * ezgl::Window::getHeight() * 3, 0);

		std::vector<cl_double2> points(_nbPoints);
		for (int i = 0; i < points.size(); i++)
			points[i] = {frctl::randomDouble(-2, 0.5), frctl::randomDouble(-1.3, 1.3)};

		compute_partial(zoom, xOffset, yOffset, points, 0, _maxIterations);
		compute_partial(zoom, xOffset, yOffset, points, 1, _maxIterations / 10);
		compute_partial(zoom, xOffset, yOffset, points, 2, _maxIterations / 100);

		texture = ezgl::Texture(ezgl::Window::getWidth(), ezgl::Window::getHeight(), pixels);
		fbo.setTexture(texture);
		requireUpdate = false;
	}

	void Buddhabrot::draw()
	{
		fbo.bind();
		fbo.draw();
		fbo.unbind();
		ImGui::Begin(name.c_str());
		ImGui::Text("General");
		requireUpdate |= ImGui::SliderInt("Max Iterations", &_maxIterations, 1000, 20000);
		requireUpdate |= ImGui::SliderInt("Point Amount", &_nbPoints, 100000, 10000000);
		requireUpdate |= ImGui::SliderFloat("Brightness", &_brightness, 1, 40);
		ImGui::End();
	}
}
