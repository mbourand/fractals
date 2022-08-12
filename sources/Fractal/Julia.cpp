#include "Julia.hpp"
#include "myimgui.h"
#include <CL/cl.hpp>
#include "EZGL/Window.h"

namespace frctl
{
	Julia::Julia()
		: maxIterations(1000), controller(FractalController(0.2, -0.5, 0)), _requireUpdate(true), c({-0.67, 0.209})
	{
		name = "Julia";
		cs = ezgl::ComputeShader("../../shaders/julia.cl", "compute_fractal");
	}

	Julia::Julia(const Julia& other) { *this = other; }
	Julia& Julia::operator=(const Julia& other)
	{
		pixels = other.pixels;
		maxIterations = other.maxIterations;
		name = other.name;
		c = other.c;
		return *this;
	}

	void Julia::compute()
	{
		static std::vector<cl_float3> colors = {{{0 / 255.0f, 7 / 255.0f, 100 / 255.0f},
												 {32 / 255.0f, 107 / 255.0f, 203 / 255.0f},
												 {237 / 255.0f, 255 / 255.0f, 255 / 255.0f},
												 {255 / 255.0f, 170 / 255.0f, 0 / 255.0f},
												 {0 / 255.0f, 2 / 255.0f, 0 / 255.0f},
												 {0 / 255.0f, 7 / 255.0f, 100 / 255.0f}}};
		static unsigned int nbColors = colors.size();

		if (!_requireUpdate && !controller.requiresUpdate())
			return;

		unsigned int width = ezgl::Window::getWidth();
		unsigned int height = ezgl::Window::getHeight();

		if (pixels.size() < width * height * 3)
			pixels.resize(width * height * 3, 0);

		cl::Buffer pixelsBuffer = cs.createBuffer(CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, pixels);
		cl::Buffer colorsBuffer = cs.createBuffer(CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, colors);

		cs.setArg(0, width);
		cs.setArg(1, height);
		cs.setArg(2, controller.zoom);
		cs.setArg(3, controller.xOffset);
		cs.setArg(4, controller.yOffset);
		cs.setArg(5, pixelsBuffer);
		cs.setArg(6, colorsBuffer);
		cs.setArg(7, nbColors);
		cs.setArg(8, maxIterations);
		cs.setArg(9, c);

		cs.run(cl::NDRange(width, height));
		cs.commands.enqueueReadBuffer(pixelsBuffer, CL_TRUE, 0, pixels.size() * sizeof(uint8_t), pixels.data());
		_texture = ezgl::Texture(width, height, pixels);
		fbo.setTexture(_texture);
		_requireUpdate = false;
	}

	void Julia::draw()
	{
		fbo.bind();
		fbo.draw();
		fbo.unbind();
		ImGui::Begin(name.c_str());
		if (ImGui::SliderInt("Max Iterations", &maxIterations, 100, 20000))
			_requireUpdate = true;
		if (ImGui::SliderFloat2("c value", reinterpret_cast<float*>(&c), -1, 1))
			_requireUpdate = true;
		ImGui::End();
	}

	void Julia::dispose()
	{
		pixels.clear();
		pixels.shrink_to_fit();
	}
}