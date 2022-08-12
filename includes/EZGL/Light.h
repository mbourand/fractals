#pragma once

#include "Math/Vector.h"

namespace ezgl
{
	struct Light
	{
		Vector3<float> direction;
		Vector3<float> color;
		float intensity;

		Light(const Vector3<float>& direction, const Vector3<float>& color, float intenity);
	};
}