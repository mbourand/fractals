#include "Buddhabrot.hpp"
#include "myimgui.h"
#include "utils.h"
#include <CL/cl.hpp>
#include <algorithm>
#include "EZGL/Window.h"

namespace frctl
{
	Buddhabrot::Buddhabrot(std::vector<float>& pixels)
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
		return FractalController(this, 0.2, -0.5, 0, false);
	}

	void Buddhabrot::compute_partial(float zoom, float xOffset, float yOffset, std::vector<cl_double2>& points,
									 int colorChannel, int maxIterations)
	{
		unsigned int width = ezgl::Window::getWidth();
		unsigned int height = ezgl::Window::getHeight();

		cl::Buffer pixelsBuffer = _cs.createBuffer(CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, pixels);
		cl::Buffer pointsBuffer = _cs.createBuffer(CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, points);

		_cs.setArg(0, width);
		_cs.setArg(1, height);
		_cs.setArg(2, zoom);
		_cs.setArg(3, xOffset);
		_cs.setArg(4, yOffset);
		_cs.setArg(5, pixelsBuffer);
		_cs.setArg(6, colorChannel);
		_cs.setArg(7, pointsBuffer);
		_cs.setArg(8, maxIterations);
		_cs.setArg(9, _brightness);
		_cs.run(cl::NDRange(points.size()));

		_cs.commands.enqueueReadBuffer(pixelsBuffer, CL_TRUE, 0, pixels.size() * sizeof(float), pixels.data());
	}

	bool Buddhabrot::preset(const std::string& buttonName, int maxIterations, int nbPoints, double brightness)
	{
		if (ImGui::Button(buttonName.c_str()))
		{
			_maxIterations = maxIterations;
			_nbPoints = nbPoints;
			_brightness = brightness;
			return true;
		}
		return false;
	}

	void Buddhabrot::compute(float zoom, float xOffset, float yOffset)
	{
		if (!requireUpdate)
			return;

		pixels.assign(ezgl::Window::getWidth() * ezgl::Window::getHeight() * 3, 0);

		std::vector<cl_double2> points(min(50000000, _nbPoints), {0, 0});
		for (int nbPoints = _nbPoints; nbPoints > 0; nbPoints -= 50000000)
		{
			if (nbPoints < points.size())
			{
				points.resize(nbPoints);
				points.shrink_to_fit();
			}
			if (nbPoints)
				for (int i = 0; i < points.size(); i++)
					points[i] = {frctl::randomDouble(-2, 0.5), frctl::randomDouble(0, 1.3)};

			compute_partial(zoom, xOffset, yOffset, points, 0, _maxIterations);
			compute_partial(zoom, xOffset, yOffset, points, 1, _maxIterations / 10);
			compute_partial(zoom, xOffset, yOffset, points, 2, _maxIterations / 100);
		}

		texture = ezgl::Texture(ezgl::Window::getWidth(), ezgl::Window::getHeight(), pixels);
		fbo.setTexture(texture);
		requireUpdate = false;
	}

	void Buddhabrot::draw()
	{
		fbo.bind();
		fbo.draw();
		fbo.unbind();

		ImGui::Separator();
		ImGui::Text(name.c_str());

		requireUpdate |= ImGui::SliderInt("Max Iterations", &_maxIterations, 1000, 20000);

		float pointAmount = _nbPoints;
		if (ImGui::SliderInt("Point Amount", &_nbPoints, 1000000, 500000000))
		{
			requireUpdate = true;
			float ratio = _nbPoints / pointAmount;
			_brightness /= ratio; // Adjust brightness to point amount
		}

		float tmp = _brightness;
		requireUpdate |= ImGui::SliderFloat("Brightness", &tmp, 0.01, 200);
		_brightness = tmp;

		if (ImGui::Button("Default"))
		{
			init();
			requireUpdate = true;
		}

		ImGui::SameLine();
		requireUpdate |= preset("4M Points", 5000, 4000000, 52.5f);
		ImGui::SameLine();
		requireUpdate |= preset("10M Points", 5000, 10000000, 21.0f);
		ImGui::SameLine();
		requireUpdate |= preset("30M Points", 5000, 30000000, 7.0f);
		ImGui::SameLine();
		requireUpdate |= preset("50M Points", 5000, 50000000, 4.2f);
		ImGui::SameLine();
		requireUpdate |= preset("100M Points", 5000, 100000000, 2.1f);
		ImGui::SameLine();
		requireUpdate |= preset("200M Points", 5000, 200000000, 1.05f);
		ImGui::SameLine();
		requireUpdate |= preset("500M Points", 5000, 500000000, 0.42f);
	}
}
