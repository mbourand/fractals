#pragma once

#include "Math/Matrix.h"
#include <memory>

namespace ezgl
{
	class PerspectiveCamera
	{
	protected:
		float _fov, _near, _far;
		Matrix<float, 4, 4> _view, _projection;

		Vector3<float> _position;
		Vector3<float> _direction;

		float _yaw, _pitch;

	public:
		PerspectiveCamera();
		PerspectiveCamera(const PerspectiveCamera& other) = default;
		PerspectiveCamera& operator=(const PerspectiveCamera& other) = default;

		PerspectiveCamera(float fov, float near, float far);


		void move(const Vector3<float>& dir);
		void rotate(float yaw, float pitch);
		void updateProjection();

		Matrix<float, 4, 4> getMVP() const;
		const Vector3<float>& getPosition() const;
		const Vector3<float>& getDirection() const;
	};
}