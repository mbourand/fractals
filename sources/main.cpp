#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "EZGL/Window.h"
#include "EZGL/Shader.h"
#include "EZGL/Texture.h"
#include "EZGL/FrameBufferObject.h"
#include "EZGL/ComputeShader.h"
#include "FractalController.hpp"
#include "Menu.hpp"
#include "Fractal.hpp"
#include "Mandelbrot.hpp"
#include "Julia.hpp"
#include "Newton.hpp"
#include "Phoenix.hpp"
#include "Buddhabrot.hpp"

int main()
{
	if (!glfwInit())
	{
		std::cerr << "OpenGL initialization failed: glfwInit error" << std::endl;
		return 1;
	}
	glewInit();
	ezgl::Window::create("Fractals");

	try
	{
		std::vector<float> pixels;

		std::vector<frctl::Fractal*> fractals;
		fractals.push_back(new frctl::Mandelbrot(pixels));
		fractals.push_back(new frctl::Julia(pixels));
		fractals.push_back(new frctl::Newton(pixels));
		fractals.push_back(new frctl::Phoenix(pixels));
		fractals.push_back(new frctl::Buddhabrot(pixels));

		frctl::Menu menu(fractals);
		frctl::FractalController controller = menu.getSelectedFractal()->init();

		while (!ezgl::Window::shouldClose())
		{
			ezgl::Window::update();
			ezgl::Window::clear();
			ezgl::Window::beginMenu("Settings");
			if (menu.update())
				controller = menu.getSelectedFractal()->init();
			menu.getSelectedFractal()->compute(controller.zoom, controller.xOffset, controller.yOffset);
			menu.getSelectedFractal()->draw();
			ezgl::Window::endMenu();
			ezgl::Window::display();
			ezgl::Window::pollEvents();
		}
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}
	ezgl::Window::terminate();
}
