#include "EZGL/Math/Matrix.h"

namespace ezgl
{
	Matrix<float, 4, 4> lookAt(const Vector3<float>& eye, const Vector3<float>& center, const Vector3<float>& upDir)
	{
		Matrix<float, 4, 4> rotation, translation(1);
		translation.at(3, 0) = -eye.x;
		translation.at(3, 1) = -eye.y;
		translation.at(3, 2) = -eye.z;

		Vector3<float> forward = eye - center;
		Vector3<float> left, up;
		forward.normalize();
		left = upDir.cross(forward);
		left.normalize();
		up = forward.cross(left);
		up.normalize();

		rotation.at(0, 0) = left.x;
		rotation.at(1, 0) = left.y;
		rotation.at(2, 0) = left.z;
		rotation.at(0, 1) = up.x;
		rotation.at(1, 1) = up.y;
		rotation.at(2, 1) = up.z;
		rotation.at(0, 2) = forward.x;
		rotation.at(1, 2) = forward.y;
		rotation.at(2, 2) = forward.z;
		rotation.at(3, 3) = 1;

		return rotation * translation;
	}

	Matrix<float, 4, 4> translation(const Vector3<float>& pos)
	{
		Matrix<float, 4, 4> translation;
		translation.at(0, 0) = 1;
		translation.at(1, 1) = 1;
		translation.at(2, 2) = 1;
		translation.at(3, 3) = 1;
		translation.at(3, 0) = pos.x;
		translation.at(3, 1) = pos.y;
		translation.at(3, 2) = pos.z;
		return translation;
	}

	Matrix<float, 4, 4> perspective(float fov, float ratio, float near, float far)
	{
		Matrix<float, 4, 4> perspective;

		float mid_angle = std::tan(fov / 2.0f);

		perspective.at(0, 0) = 1 / (ratio * mid_angle);
		perspective.at(1, 1) = 1 / mid_angle;
		perspective.at(2, 2) = -(far + near) / (far - near);
		perspective.at(3, 2) = -2 * far * near / (far - near);
		perspective.at(2, 3) = -1;

		return perspective;
	}
}
