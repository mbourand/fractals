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

int main()
{
	if (!glfwInit())
	{
		std::cerr << "OpenGL initialization failed: glfwInit error" << std::endl;
		return 1;
	}
	glewInit();
	ezgl::Window::create("Fractals");

	std::vector<uint8_t> pixels;

	std::vector<frctl::Fractal*> fractals;
	fractals.push_back(new frctl::Mandelbrot(pixels));
	fractals.push_back(new frctl::Julia(pixels));
	fractals.push_back(new frctl::Newton(pixels));

	frctl::Menu menu(fractals);
	frctl::FractalController controller = menu.getSelectedFractal()->init();

	while (!ezgl::Window::shouldClose())
	{
		ezgl::Window::update();
		menu.getSelectedFractal()->compute(controller.zoom, controller.xOffset, controller.yOffset);
		ezgl::Window::clear();
		menu.getSelectedFractal()->draw();
		if (menu.update())
			controller = menu.getSelectedFractal()->init();
		ezgl::Window::display();
		ezgl::Window::pollEvents();
	}

	ezgl::Window::terminate();
}
