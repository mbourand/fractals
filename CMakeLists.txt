cmake_minimum_required(VERSION 3.23)

project(fractals)

set(CMAKE_CXX_STANDARD 20)

# Sources

add_executable(${PROJECT_NAME}
	sources/main.cpp
	sources/FractalController.cpp
	sources/Fractal/Mandelbrot.cpp
	sources/Fractal/Julia.cpp
	sources/Menu.cpp
	sources/utils.cpp
	sources/EZGL/FlyController.cpp
	sources/EZGL/KeyListener.cpp
	sources/EZGL/Light.cpp
	sources/EZGL/Material.cpp
	sources/EZGL/Mesh.cpp
	sources/EZGL/MouseListener.cpp
	sources/EZGL/PerspectiveCamera.cpp
	sources/EZGL/FrameBufferObject.cpp
	sources/EZGL/ComputeShader.cpp
	sources/EZGL/Shader.cpp
	sources/EZGL/Texture.cpp
	sources/EZGL/VertexBuffer.cpp
	sources/EZGL/Window.cpp
	sources/EZGL/Math/mathutils.cpp
	sources/EZGL/Math/Matrix.cpp
	external/ImGui/imgui.cpp
	external/ImGui/imgui_demo.cpp
	external/ImGui/imgui_draw.cpp
	external/ImGui/imgui_tables.cpp
	external/ImGui/imgui_widgets.cpp
	external/ImGui/backends/imgui_impl_glfw.cpp
	external/ImGui/backends/imgui_impl_opengl3.cpp
)

# Building Libs

find_package(CUDAToolkit REQUIRED)

add_subdirectory(external/GLFW)
add_subdirectory(external/GLEW)

# Linking

target_include_directories(${PROJECT_NAME}
	PUBLIC includes/
	PUBLIC includes/Fractal
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/GLFW/include/
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/GLEW/include/
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/GLM
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/IMGUI
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/IMGUI/backends
	PUBLIC $ENV{CUDA_PATH}/include
)

target_link_libraries(${PROJECT_NAME}
	glfw ${GLFW_LIBRARIES}
	libglew_static
	opengl32
	${CUDA_OpenCL_LIBRARY}
)
