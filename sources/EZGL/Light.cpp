#include "EZGL/Light.h"
#include "EZGL/Math/Vector.h"

namespace ezgl
{
	Light::Light(const Vector3<float>& direction, const Vector3<float>& color, float intensity)
	{
		this->direction = direction;
		this->color = color;
		this->intensity = intensity;
	}
}
