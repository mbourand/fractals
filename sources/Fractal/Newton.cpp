#include "Newton.hpp"
#include "myimgui.h"
#include <CL/cl.hpp>
#include "EZGL/Window.h"

namespace frctl
{
	Newton::Newton(std::vector<float>& pixels)
		: Fractal("Newton", pixels), _maxIterations(Newton::DEFAULT_MAX_ITERATIONS), _a(Newton::DEFAULT_A)
	{
		_cs = ezgl::ComputeShader({"shaders/utils.cl", "shaders/newton.cl"}, "compute_fractal");
		_points.push_back({1, 0});
		_points.push_back({-.5, 0.86602});
		_points.push_back({-.5, -0.86602});
	}

	Newton::Newton(const Newton& other) : Fractal(other.name, other.pixels) { *this = other; }
	Newton& Newton::operator=(const Newton& other)
	{
		Fractal::operator=(other);
		_maxIterations = other._maxIterations;
		_a = other._a;
		_points = other._points;
		return *this;
	}

	FractalController Newton::init()
	{
		_maxIterations = Newton::DEFAULT_MAX_ITERATIONS;
		_a = Newton::DEFAULT_A;
		return FractalController(this, 0.1, 0, 0);
	};

	void Newton::compute(float zoom, float xOffset, float yOffset)
	{
		static std::vector<cl_float3> colors = {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};

		if (!requireUpdate)
			return;

		unsigned int nbColors = colors.size();
		unsigned int width = ezgl::Window::getWidth();
		unsigned int height = ezgl::Window::getHeight();

		if (pixels.size() < width * height * 3)
			pixels.resize(width * height * 3, 0);

		cl::Buffer pixelsBuffer = _cs.createBuffer(CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, pixels);
		cl::Buffer colorsBuffer = _cs.createBuffer(CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, colors);
		cl::Buffer pointsBuffer = _cs.createBuffer(CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, _points);

		_cs.setArg(0, width);
		_cs.setArg(1, height);
		_cs.setArg(2, zoom);
		_cs.setArg(3, xOffset);
		_cs.setArg(4, yOffset);
		_cs.setArg(5, pixelsBuffer);
		_cs.setArg(6, colorsBuffer);
		_cs.setArg(7, nbColors);
		_cs.setArg(8, _maxIterations);
		_cs.setArg(9, _a);
		_cs.setArg(10, pointsBuffer);

		_cs.run(cl::NDRange(width, height));
		_cs.commands.enqueueReadBuffer(pixelsBuffer, CL_TRUE, 0, pixels.size() * sizeof(float), pixels.data());
		texture = ezgl::Texture(width, height, pixels);
		fbo.setTexture(texture);
		requireUpdate = false;
	}

	void Newton::draw()
	{

		fbo.bind();
		fbo.draw();
		fbo.unbind();
		ImGui::Separator();
		ImGui::Text(name.c_str());
		requireUpdate |= ImGui::SliderInt("Max Iterations", &_maxIterations, 100, 20000);
		requireUpdate |= ImGui::SliderFloat("a value", &_a, 0.1, 1.95);
	}
}
