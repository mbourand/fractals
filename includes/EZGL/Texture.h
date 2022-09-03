#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace ezgl
{
	class Texture
	{
	protected:
		GLuint _id;
		unsigned int _width;
		unsigned int _height;

	public:
		Texture() = default;
		Texture(unsigned int width, unsigned int height, const std::vector<float>& pixels);
		Texture(const Texture& other) = default;
		Texture& operator=(const Texture& other) = default;

		inline GLuint getId() const { return _id; }
		inline unsigned int getWidth() const { return _width; }
		inline unsigned int getHeight() const { return _height; }

		void bind();
		void unbind();
	};
}
