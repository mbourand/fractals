#pragma once

#include <vector>
#include "Math/Vector.h"

namespace ezgl
{
	class Mesh
	{
	protected:
		std::vector<float> _positions;
		std::vector<float> _normals;
		std::vector<float> _colors;

	public:
		Mesh() = default;
		Mesh(const Mesh& other) = default;
		Mesh& operator=(const Mesh& other) = default;

		void addPoint(const Vector3<float>& vec);
		void addColor(const Vector3<float>& vec);
		void addNormal(const Vector3<float>& vec);

		size_t getByteSize() const;
		size_t getPositionsByteSize() const;
		size_t getNormalsByteSize() const;
		size_t getColorsByteSize() const;
		std::vector<float> getPositions() const;
		std::vector<float> getNormals() const;
		std::vector<float> getColors() const;
		size_t getDataTypeSize() const;
	};
}
