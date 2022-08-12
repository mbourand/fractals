#include "EZGL/Texture.h"
#include <vector>
#include <iostream>

namespace ezgl
{
	Texture::Texture(unsigned int width, unsigned int height, std::vector<unsigned char> pixels)
	{
		_width = width;
		_height = height;
		glGenTextures(1, &(this->_id));
		this->bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
		glGenerateMipmap(GL_TEXTURE_2D);
		this->unbind();
	}

	void Texture::bind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->_id);
	}

	void Texture::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }
}
