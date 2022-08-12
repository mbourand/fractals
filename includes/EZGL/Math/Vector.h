#pragma once

#include <array>
#include <glm/glm.hpp>

namespace ezgl
{
	/*
	** VECTOR 3
	*/
	template<typename T> class Vector4;

	template<typename T>
	class Vector3
	{
	public:
		T x, y, z;

		Vector3<T>()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		Vector3<T>(const T& x, const T& y, const T& z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3<T>(const Vector4<T>& v4)
		{
			this->x = v4.x;
			this->y = v4.y;
			this->z = v4.z;
		}

		Vector3<T>(const Vector3<T>& other) = default;
		Vector3<T>& operator=(const Vector3<T>& other) = default;

		Vector3<T> operator*(const Vector3<T>& other) const
		{
			Vector3<T> cpy = *this;
			cpy.x = this->x * other.x;
			cpy.y = this->y * other.y;
			cpy.z = this->z * other.z;
			return cpy;
		}

		Vector3<T> operator*=(const Vector3<T>& other)
		{
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			return *this;
		}

		Vector3<T> operator*(const T& x) const
		{
			Vector3<T> cpy = *this;
			cpy.x = this->x * x;
			cpy.y = this->y * x;
			cpy.z = this->z * x;
			return cpy;
		}

		Vector3<T> operator*=(const T& x)
		{
			this->x *= x;
			this->y *= x;
			this->z *= x;
			return *this;
		}

		Vector3<T> operator+(const Vector3<T>& other) const
		{
			Vector3<T> cpy = *this;
			cpy.x = this->x + other.x;
			cpy.y = this->y + other.y;
			cpy.z = this->z + other.z;
			return cpy;
		}

		Vector3<T> operator+=(const Vector3<T>& other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			return *this;
		}

		Vector3<T> operator-(const Vector3<T>& other) const
		{
			Vector3<T> cpy = *this;
			cpy.x = this->x - other.x;
			cpy.y = this->y - other.y;
			cpy.z = this->z - other.z;
			return cpy;
		}

		Vector3<T> operator-=(const Vector3<T>& other)
		{
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			return *this;
		}

		Vector3<T> operator/(const Vector3<T>& other) const
		{
			Vector3<T> cpy = *this;
			cpy.x = this->x / other.x;
			cpy.y = this->y / other.y;
			cpy.z = this->z / other.z;
			return cpy;
		}

		Vector3<T> operator/=(const Vector3<T>& other)
		{
			this->x /= other.x;
			this->y /= other.y;
			this->y /= other.z;
			return *this;
		}

		float length() const
		{
			return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
		}

		glm::vec3 toGLM() const
		{
			return glm::vec3(this->x, this->y, this->z);
		}

		Vector3<T> normalize()
		{
			float length = this->length();
			this->x /= length;
			this->y /= length;
			this->z /= length;
			return *this;
		}

		Vector3<T> cross(const Vector3<T>& other) const
		{
			return Vector3<T>(
				this->y * other.z - other.y * this->z,
				this->z * other.x - other.z * this->x,
				this->x * other.y - other.x * this->y
			);
		}
	};

	
	/*
	** VECTOR 4
	*/
	template<typename T>
	class Vector4
	{
	public:
		T x, y, z, w;

		Vector4<T>()
		{}

		Vector4<T>(const T& x, const T& y, const T& z, const T& w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vector4<T>(const Vector3<T>& v3)
		{
			this->x = v3.x;
			this->y = v3.y;
			this->z = v3.z;
			this->w = 1.0f;
		}

		Vector4<T>(const Vector4<T>& other) = default;
		Vector4<T>& operator=(const Vector4<T>& other) = default;

		Vector4<T> operator*(const Vector4<T>& other) const
		{
			Vector3<T> cpy = *this;
			cpy.x = this->x * other.x;
			cpy.y = this->y * other.y;
			cpy.z = this->z * other.z;
			cpy.w = this->w * other.w;
			return cpy;
		}

		Vector4<T> operator*=(const Vector4<T>& other)
		{
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			this->w *= other.w;
			return *this;
		}

		Vector3<T> operator*(const T& x) const
		{
			Vector3<T> cpy = *this;
			cpy.x = this->x * x;
			cpy.y = this->y * x;
			cpy.z = this->z * x;
			cpy.w = this->w * x;
			return cpy;
		}

		Vector3<T> operator*=(const T& x)
		{
			this->x *= x;
			this->y *= x;
			this->z *= x;
			this->w *= x;
			return *this;
		}

		Vector4<T> operator+(const Vector4<T>& other) const
		{
			Vector4<T> cpy = *this;
			cpy.x = this->x + other.x;
			cpy.y = this->y + other.y;
			cpy.z = this->z + other.z;
			cpy.w = this->w + other.w;
			return cpy;
		}

		Vector4<T> operator+=(const Vector4<T>& other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			this->w += other.w;
			return *this;
		}

		Vector4<T> operator-(const Vector4<T>& other) const
		{
			Vector4<T> cpy = *this;
			cpy.x = this->x - other.x;
			cpy.y = this->y - other.y;
			cpy.z = this->z - other.z;
			cpy.w = this->w - other.w;

			return cpy;
		}

		Vector4<T> operator-=(const Vector4<T>& other)
		{
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			this->w -= other.w;
			return *this;
		}

		Vector4<T> operator/(const Vector4<T>& other) const
		{
			Vector4<T> cpy = *this;
			cpy.x = this->x / other.x;
			cpy.y = this->y / other.y;
			cpy.z = this->z / other.z;
			cpy.w = this->w / other.w;
			return cpy;
		}

		Vector4<T> operator/=(const Vector4<T>& other)
		{
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;
			this->w /= other.w;
			return *this;
		}

		float length() const
		{
			return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
		}

		Vector4<T> normalize()
		{
			float length = this->length();
			this->x /= length;
			this->y /= length;
			this->z /= length;
			this->w /= length;
			return *this;
		}

		glm::vec4 toGLM() const
		{
			return glm::vec4(this->x, this->y, this->z, this->w);
		}
	};
}