#pragma once

#include <string>
#include "EZGL/FrameBufferObject.h"

namespace frctl
{
	class Fractal
	{
	public:
		std::string name;
		ezgl::FrameBufferObject fbo;

		virtual void compute() = 0;
		virtual void draw() = 0;
		virtual void dispose() = 0;

		virtual ~Fractal() {};
	};
}
