#include "EZGL/PerspectiveCamera.h"
#include "EZGL/Math/mathutils.h"
#include "EZGL/Window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ezgl
{
	PerspectiveCamera::PerspectiveCamera()
	{
		this->_fov = 0;
		this->_near = 0;
		this->_far = 0;
		this->_view = Matrix<float, 4, 4>(1);
		this->_projection = Matrix<float, 4, 4>(1);
		this->_yaw = 0;
		this->_pitch = 0;
	}

	PerspectiveCamera::PerspectiveCamera(float fov, float near, float far)
	{
		this->_fov = fov;
		this->_near = near;
		this->_far = far;

		this->_position = Vector3<float>(0, 0, 5);
		
		this->_direction = Vector3<float>(0, 0, -1);
		this->_direction.normalize();
		this->_yaw = -90.0f;
		this->_pitch = 0;

		this->_view = ezgl::lookAt(this->_position, this->_position + this->_direction, Vector3<float>(0.0f, 1.0f, 0.0f));
		this->_projection = ezgl::perspective(glm::radians(this->_fov), ezgl::Window::getWidth() / static_cast<float>(ezgl::Window::getHeight()), this->_near, this->_far);
	}

	void PerspectiveCamera::updateProjection()
	{
		this->_projection = ezgl::perspective(glm::radians(this->_fov), ezgl::Window::getWidth() / static_cast<float>(ezgl::Window::getHeight()), this->_near, this->_far);
	}

	void PerspectiveCamera::move(const Vector3<float>& dir)
	{
		this->_position += dir;
		this->_view = ezgl::lookAt(this->_position, this->_position + this->_direction, Vector3<float>(0.0f, 1.0f, 0.0f));
	}

	// https://learnopengl.com/Getting-started/Camera
	void PerspectiveCamera::rotate(float yaw, float pitch)
	{
		this->_yaw += yaw;
		this->_pitch += pitch;

		if (this->_pitch > 89.0f)
			this->_pitch = 89.0f;
		if (this->_pitch < -89.0f)
			this->_pitch = -89.0f;

		this->_direction.x = std::cos(ezgl::radians(this->_yaw)) * std::cos(ezgl::radians(this->_pitch));
		this->_direction.y = std::sin(ezgl::radians(this->_pitch));
		this->_direction.z = std::sin(ezgl::radians(this->_yaw)) * std::cos(ezgl::radians(this->_pitch));
		this->_direction.normalize();
		
		this->_view = ezgl::lookAt(this->_position, this->_position + this->_direction, Vector3<float>(0.0f, 1.0f, 0.0f));
	}

	Matrix<float, 4, 4> PerspectiveCamera::getMVP() const
	{
		return this->_projection * this->_view;
	}

	const Vector3<float>& PerspectiveCamera::getPosition() const { return this->_position; }
	const Vector3<float>& PerspectiveCamera::getDirection() const { return this->_direction; };
}
