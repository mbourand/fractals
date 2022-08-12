#include "EZGL/Material.h"

namespace ezgl
{
	Material::Material(const Vector3<float>& color, float ambient, float diffuse, float specular, float shininess)
	{
		this->color = color;
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->shininess = shininess;
	}
}
