#pragma once

#include <array>
#include <iostream>
#include "Vector.h"

namespace ezgl
{
	template<typename T, unsigned int W, unsigned int H>
	class Matrix
	{
	protected:
		std::array<std::array<T, W>, H> _values;

	public:
		Matrix<T, W, H>()
		{
			this->_values = std::array<std::array<T, W>, H>();
			for (auto& elem : this->_values)
				elem.fill(T());
		}
		
		Matrix<T, W, H>(const Matrix<T, W, H>& other)
		{
			*this = other;
		}

		Matrix<T, W, H>(const T& value)
		{
			this->_values = std::array<std::array<T, W>, H>();
			for (size_t offset = 0; offset < std::min(W, H); offset++)
				this->at(offset, offset) = value;
		}

		const T& at(unsigned int x, unsigned int y) const
		{
			return this->_values[y][x];
		}

		T& at(unsigned int x, unsigned int y)
		{
			return this->_values[y][x];
		}

		Matrix<T, W, H> operator+(const Matrix<T, W, H>& other) const
		{
			Matrix<T, W, H> cpy = *this;
			for (unsigned int x = 0; x < W; x++)
				for (unsigned int y = 0; y < H; y++)
					cpy.at(x, y) += other.at(x, y);
			return cpy;
		}

		Matrix<T, W, H> operator+=(const Matrix<T, W, H>& other)
		{
			*this = *this + other;
			return *this;
		}

		Matrix<T, W, H> operator-(const Matrix<T, W, H>& other) const
		{
			Matrix<T, W, H> cpy = *this;
			for (unsigned int x = 0; x < W; x++)
				for (unsigned int y = 0; y < H; y++)
					cpy.at(x, y) -= other.at(x, y);
			return cpy;
		}

		Matrix<T, W, H> operator-=(const Matrix<T, W, H>& other)
		{
			*this = *this - other;
			return *this;
		}

		Matrix<T, H, H> operator*(const Matrix<T, H, W>& other) const
		{
			Matrix<T, H, H> res;
			for (unsigned int y = 0; y < H; y++)
				for (unsigned int x = 0; x < H; x++)
					for (unsigned int offset = 0; offset < W; offset++)
						res.at(x, y) += this->at(offset, y) * other.at(x, offset);
			return res;
		}

		Matrix<T, W, H>& operator=(const Matrix<T, W, H>& other)
		{
			this->_values = other._values;
			return *this;
		}

		bool operator==(const Matrix<T, W, H>& other) const
		{
			return this->_values == other._values;
		}

		bool operator!=(const Matrix<T, W, H>& other) const
		{
			return !(this->_values == other._values);
		}

	};

	template<typename T, unsigned int W, unsigned int H>
	std::ostream& operator<<(std::ostream& os, const Matrix<T, W, H>& matrix)
	{
		std::cout << "[\n";
		for (unsigned int y = 0; y < H; y++)
		{
			std::cout << "  [";
			for (unsigned int x = 0; x < W; x++)
			{
				std::cout << matrix.at(x, y);
				if (x != W - 1)
					std::cout << ", ";
			}
			std::cout << "]\n";
		}
		std::cout << "]";
		return os;
	}

	template<typename T, unsigned int SideSize>
	struct MatrixData
	{
		T data[SideSize * SideSize];

		MatrixData<T, SideSize>(const Matrix<T, SideSize, SideSize>& matrix)
		{
			for (size_t y = 0; y < SideSize; y++)
				for (size_t x = 0; x < SideSize; x++)
					data[y * SideSize + x] = matrix.at(y, x);
		}
	};

	Matrix<float, 4, 4> lookAt(const Vector3<float>& eye, const Vector3<float>& center, const Vector3<float>& upDir);
	Matrix<float, 4, 4> perspective(float fov, float ratio, float near, float far);
	Matrix<float, 4, 4> translation(const Vector3<float>& pos);
}

