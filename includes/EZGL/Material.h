#pragma once

#include "Math/Vector.h"

namespace ezgl
{
	struct Material
	{
		Vector3<float> color;
		float ambient;
		float diffuse;
		float specular;
		float shininess;

		Material(const Vector3<float>& color, float ambient, float diffuse, float specular, float shininess);
	};
}