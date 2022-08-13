#pragma once

#include <string>
#include "EZGL/FrameBufferObject.h"
#include "EZGL/Texture.h"

namespace frctl
{
	class FractalController;

	class Fractal
	{
	public:
		std::string name;
		ezgl::FrameBufferObject fbo;
		std::vector<uint8_t>& pixels;
		ezgl::Texture texture;
		bool requireUpdate;

		Fractal(const std::string& name, std::vector<uint8_t>& pixels);
		Fractal& operator=(const Fractal& other);

		virtual void compute(float zoom, float xOffset, float yOffset) = 0;
		virtual void draw() = 0;
		virtual FractalController init() = 0;

		virtual ~Fractal() {};
	};
}
