#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Mesh.h"

namespace ezgl
{
	class VertexBuffer
	{
	protected:
		GLuint _vbo, _vao;
		size_t _vertricesCount;

	public:
		VertexBuffer();
		VertexBuffer(const VertexBuffer& other) = default;
		VertexBuffer& operator=(const VertexBuffer& other) = default;

		VertexBuffer(const Shader& shader, const Mesh& mesh);

		void bind() const;
		void setData(const Shader& shader, const Mesh& mesh);
		void draw() const;
		void unbind() const;
	};
}
