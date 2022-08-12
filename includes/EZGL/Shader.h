#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Math/Matrix.h"
#include "Light.h"
#include "Material.h"

namespace ezgl
{
	class Shader
	{
	protected:
		unsigned int _programId;

	private:
		unsigned int _compileShader(unsigned int type, const std::string& source);

	public:
		Shader();
		Shader(const Shader& other);
		Shader& operator=(const Shader& other);
		Shader(const std::string& vertexFilename, const std::string& fragFilename);
		void loadFile(GLuint type, const std::string& path);
		void loadFiles(const std::string& vertexPath, const std::string& fragPath);

		void sendUniform(const std::string& name, const Matrix<float, 4, 4>& data) const;
		void sendUniform(const std::string& name, const Light& light) const;
		void sendUniform(const std::string& name, const Material& material) const;
		void sendUniform(const std::string& name, const Vector3<float>& vec) const;
		void sendUniform(const std::string& name, float value) const;
		void sendUniform(const std::string& name, const std::vector<float>& value) const;

		void bind() const;
		void unbind() const;

		int getProgramId() const;
	};
}
