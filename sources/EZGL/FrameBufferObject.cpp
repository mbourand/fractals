#include "EZGL/FrameBufferObject.h"
#include "EZGL/Window.h"

namespace ezgl
{
	FrameBufferObject::FrameBufferObject() { glGenFramebuffers(1, &_fbo); }

	FrameBufferObject::FrameBufferObject(const Texture& texture)
	{
		glGenFramebuffers(1, &_fbo);
		setTexture(texture);
	}

	void FrameBufferObject::bind() const { glBindFramebuffer(GL_READ_FRAMEBUFFER, _fbo); }

	void FrameBufferObject::setTexture(const Texture& texture)
	{
		bind();
		_width = texture.getWidth();
		_height = texture.getHeight();
		glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getId(), 0);
		unbind();
	}

	void FrameBufferObject::draw() const
	{
		glBlitFramebuffer(0, 0, _width, _height, 0, 0, ezgl::Window::getWidth(), ezgl::Window::getHeight(),
						  GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}

	void FrameBufferObject::unbind() const { glBindFramebuffer(GL_READ_FRAMEBUFFER, 0); }
}
