#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>
#include "EZGL/Window.h"
#include "EZGL/KeyListener.h"
#include "EZGL/MouseListener.h"
#include <chrono>

namespace ezgl
{
	GLFWwindow* Window::_window = nullptr;
	unsigned int Window::_width = 0;
	unsigned int Window::_height = 0;

	void Window::create(const std::string& title)
	{
		GLFWmonitor* screenMode = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(screenMode);

		_width = mode->width * 0.9;
		_height = mode->height * 0.9;
		_window = glfwCreateWindow(_width, _height, title.c_str(), nullptr, nullptr);
		glfwSetWindowPos(_window, mode->width / 2 - _width / 2, mode->height / 2 - _height / 2);
		if (!_window)
		{
			glfwTerminate();
			throw std::runtime_error("Failed to create the window");
		}

		glfwMakeContextCurrent(_window);

		if (glewInit() != GLEW_OK)
		{
			glfwTerminate();
			throw std::runtime_error("Failed to create the window");
		}

		glfwSetKeyCallback(_window, ezgl::keyCallback);
		glfwSetInputMode(_window, GLFW_STICKY_KEYS, 1);

		glfwSetCursorPosCallback(_window, ezgl::mousePosCallback);
		glfwSetCursorEnterCallback(_window, ezgl::mouseEnterCallback);
		glfwSetMouseButtonCallback(_window, ezgl::mouseButtonCallback);
		glfwSetScrollCallback(_window, ezgl::scrollCallback);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = nullptr;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(_window, true);
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void Window::clear()
	{
		glViewport(0, 0, _width, _height);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
	}

	void Window::beginMenu(const std::string& name)
	{
		ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	}

	void Window::endMenu() { ImGui::End(); }

	void Window::update()
	{
		using namespace std::chrono;
		static auto lastUpdate = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		auto now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		auto deltaTime = now - lastUpdate;
		if (deltaTime > 0)
			ezgl::updateKeyListeners(deltaTime / 1000.0f);

		lastUpdate = now;
	}

	void Window::terminate()
	{
		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
		glfwTerminate();
	}

	void Window::pollEvents() { glfwPollEvents(); }

	void Window::display()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(_window);
	}

	bool Window::shouldClose() { return glfwWindowShouldClose(_window); }

	void Window::showCursor() { glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }

	void Window::hideCursor() { glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); }

	void Window::centerCursor() { glfwSetCursorPos(_window, _width / 2, _height / 2); }

	unsigned int Window::getWidth() { return _width; }
	unsigned int Window::getHeight() { return _height; }
	void Window::setWidth(unsigned int width) { _width = width; }
	void Window::setHeight(unsigned int height) { _height = height; };
	bool Window::mouseIsOnImGuiElement() { return ImGui::GetIO().WantCaptureMouse; };
	GLFWwindow* Window::getPtr() { return _window; }
}
