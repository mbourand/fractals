#include "Julia.hpp"
#include "myimgui.h"
#include <CL/cl.hpp>
#include "EZGL/Window.h"

namespace frctl
{
	Julia::Julia(std::vector<uint8_t>& pixels) : Fractal("Julia", pixels), _maxIterations(1000), _c({-0.67, 0.209})
	{
		_cs = ezgl::ComputeShader({"../../shaders/utils.cl", "../../shaders/julia.cl"}, "compute_fractal");
	}

	Julia::Julia(const Julia& other) : Fractal(other.name, other.pixels) { *this = other; }
	Julia& Julia::operator=(const Julia& other)
	{
		Fractal::operator=(other);
		_maxIterations = other._maxIterations;
		_c = other._c;
		return *this;
	}

	FractalController Julia::init() { return FractalController(this, 0.2, 0, 0); };

	void Julia::compute(float zoom, float xOffset, float yOffset)
	{
		static std::vector<cl_float3> colors = {{{0 / 255.0f, 7 / 255.0f, 100 / 255.0f},
												 {32 / 255.0f, 107 / 255.0f, 203 / 255.0f},
												 {237 / 255.0f, 255 / 255.0f, 255 / 255.0f},
												 {255 / 255.0f, 170 / 255.0f, 0 / 255.0f},
												 {0 / 255.0f, 2 / 255.0f, 0 / 255.0f},
												 {0 / 255.0f, 7 / 255.0f, 100 / 255.0f}}};
		static unsigned int nbColors = colors.size();

		if (!requireUpdate)
			return;

		unsigned int width = ezgl::Window::getWidth();
		unsigned int height = ezgl::Window::getHeight();

		if (pixels.size() < width * height * 3)
			pixels.resize(width * height * 3, 0);

		cl::Buffer pixelsBuffer = _cs.createBuffer(CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, pixels);
		cl::Buffer colorsBuffer = _cs.createBuffer(CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, colors);

		_cs.setArg(0, width);
		_cs.setArg(1, height);
		_cs.setArg(2, zoom);
		_cs.setArg(3, xOffset);
		_cs.setArg(4, yOffset);
		_cs.setArg(5, pixelsBuffer);
		_cs.setArg(6, colorsBuffer);
		_cs.setArg(7, nbColors);
		_cs.setArg(8, _maxIterations);
		_cs.setArg(9, _c);

		_cs.run(cl::NDRange(width, height));
		_cs.commands.enqueueReadBuffer(pixelsBuffer, CL_TRUE, 0, pixels.size() * sizeof(uint8_t), pixels.data());
		texture = ezgl::Texture(width, height, pixels);
		fbo.setTexture(texture);
		requireUpdate = false;
	}

	void Julia::draw()
	{
		fbo.bind();
		fbo.draw();
		fbo.unbind();
		ImGui::Begin(name.c_str());
		if (ImGui::SliderInt("Max Iterations", &_maxIterations, 100, 20000))
			requireUpdate = true;
		if (ImGui::SliderFloat2("c value", reinterpret_cast<float*>(&_c), -1, 1))
			requireUpdate = true;
		ImGui::End();
	}
}
