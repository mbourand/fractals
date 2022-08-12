#include "EZGL/VertexBuffer.h"

namespace ezgl
{
	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &(this->_vbo));
		glGenVertexArrays(1, &(this->_vao));
		this->_vertricesCount = 0;
	}

	VertexBuffer::VertexBuffer(const Shader& shader, const Mesh& mesh)
	{
		glGenBuffers(1, &(this->_vbo));
		glGenVertexArrays(1, &(this->_vao));
		this->bind();
		this->setData(shader, mesh);
		this->unbind();
	}

	void VertexBuffer::bind() const
	{
		glBindVertexArray(this->_vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
	}

	void VertexBuffer::setData(const Shader& shader, const Mesh& mesh)
	{
		this->_vertricesCount = mesh.getPositions().size();

		glBufferData(GL_ARRAY_BUFFER, mesh.getByteSize(), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, mesh.getPositionsByteSize(), mesh.getPositions().data());
		glBufferSubData(GL_ARRAY_BUFFER, mesh.getPositionsByteSize(), mesh.getNormalsByteSize(), mesh.getNormals().data());
		glBufferSubData(GL_ARRAY_BUFFER, mesh.getPositionsByteSize() + mesh.getNormalsByteSize(), mesh.getColorsByteSize(), mesh.getColors().data());
		
		GLint location = glGetAttribLocation(shader.getProgramId(), "a_position");
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * static_cast<GLsizei>(mesh.getDataTypeSize()), reinterpret_cast<void*>(0x0));

		location = glGetAttribLocation(shader.getProgramId(), "a_normal");
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * static_cast<GLsizei>(mesh.getDataTypeSize()), reinterpret_cast<void*>(mesh.getPositionsByteSize()));

		location = glGetAttribLocation(shader.getProgramId(), "a_color");
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 3 * static_cast<GLsizei>(mesh.getDataTypeSize()), reinterpret_cast<void*>(mesh.getPositionsByteSize() + mesh.getNormalsByteSize()));
	}

	void VertexBuffer::draw() const
	{
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(this->_vertricesCount));
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}
