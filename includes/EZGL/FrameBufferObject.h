#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

namespace ezgl
{
	class FrameBufferObject
	{
	protected:
		GLuint _fbo;
		unsigned int _width;
		unsigned int _height;

	public:
		FrameBufferObject();
		FrameBufferObject(const FrameBufferObject& other) = default;
		FrameBufferObject& operator=(const FrameBufferObject& other) = default;

		FrameBufferObject(const Texture& texture);

		void bind() const;
		void setTexture(const Texture& texture);
		void draw() const;
		void unbind() const;
	};
}
