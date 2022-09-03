#include "Phoenix.hpp"
#include "myimgui.h"
#include <CL/cl.hpp>
#include "EZGL/Window.h"

namespace frctl
{
	Phoenix::Phoenix(std::vector<float>& pixels)
		: Fractal("Phoenix", pixels), _maxIterations(Phoenix::DEFAULT_MAX_ITERATIONS), _c(Phoenix::DEFAULT_C),
		  _p(Phoenix::DEFAULT_P)
	{
		_cs = ezgl::ComputeShader({"../../shaders/utils.cl", "../../shaders/phoenix.cl"}, "compute_fractal");
	}

	Phoenix::Phoenix(const Phoenix& other) : Fractal(other.name, other.pixels) { *this = other; }
	Phoenix& Phoenix::operator=(const Phoenix& other)
	{
		Fractal::operator=(other);
		_maxIterations = other._maxIterations;
		_c = other._c;
		_p = other._p;
		return *this;
	}

	FractalController Phoenix::init()
	{
		_maxIterations = Phoenix::DEFAULT_MAX_ITERATIONS;
		_c = Phoenix::DEFAULT_C;
		_p = Phoenix::DEFAULT_P;
		return FractalController(this, 0.25, 0, -0.1);
	};

	void Phoenix::compute(float zoom, float xOffset, float yOffset)
	{
		static std::vector<cl_float3> colors = {{{0 / 255.0f, 7 / 255.0f, 100 / 255.0f},
												 {32 / 255.0f, 107 / 255.0f, 203 / 255.0f},
												 {237 / 255.0f, 255 / 255.0f, 255 / 255.0f},
												 {255 / 255.0f, 170 / 255.0f, 0 / 255.0f},
												 {0 / 255.0f, 2 / 255.0f, 0 / 255.0f},
												 {0 / 255.0f, 7 / 255.0f, 100 / 255.0f}}};

		if (!requireUpdate)
			return;

		unsigned int nbColors = colors.size();
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
		_cs.setArg(10, _p);

		_cs.run(cl::NDRange(width, height));
		_cs.commands.enqueueReadBuffer(pixelsBuffer, CL_TRUE, 0, pixels.size() * sizeof(float), pixels.data());
		texture = ezgl::Texture(width, height, pixels);
		fbo.setTexture(texture);
		requireUpdate = false;
	}

	void Phoenix::draw()
	{
		fbo.bind();
		fbo.draw();
		fbo.unbind();
		ImGui::Separator();
		ImGui::Text(name.c_str());
		requireUpdate |= ImGui::SliderInt("Max Iterations", &_maxIterations, 100, 20000);
		requireUpdate |= ImGui::SliderFloat2("c value", reinterpret_cast<float*>(&_c), -1, 1);
		requireUpdate |= ImGui::SliderFloat2("p value", reinterpret_cast<float*>(&_p), -1, 1);
		ImGui::Spacing();
		ImGui::Text("Presets");
		if (ImGui::Button("Default"))
		{
			init();
			requireUpdate = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("Preset 2"))
		{
			_maxIterations = 3000;
			_c = {0.269, 0};
			_p = {0, 0.01};
			requireUpdate = true;
		}
	}
}
