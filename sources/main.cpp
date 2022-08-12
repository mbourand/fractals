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

int main()
{
	if (!glfwInit())
	{
		std::cerr << "OpenGL initialization failed: glfwInit error" << std::endl;
		return 1;
	}
	glewInit();

	ezgl::Window::create("Fractals");
	std::vector<frctl::Fractal*> fractals;
	fractals.push_back(new frctl::Mandelbrot());
	fractals.push_back(new frctl::Julia());
	frctl::Menu menu(fractals);

	while (!ezgl::Window::shouldClose())
	{
		ezgl::Window::update();
		menu.update();
		ezgl::Window::clear();
		menu.draw();
		ezgl::Window::display();
		ezgl::Window::pollEvents();
	}

	ezgl::Window::terminate();
}