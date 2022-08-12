#include "EZGL/ComputeShader.h"
#include <fstream>

namespace ezgl
{
	std::string ComputeShader::_getProgramSource(const std::string& filename)
	{
		std::ifstream file(filename);
		if (!file.good() || !file.is_open())
			throw std::runtime_error("Could not open kernel file: " + filename);
		std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		return str;
	}

	ComputeShader::ComputeShader(const std::string& filename, const std::string& kernel)
	{
		std::vector<cl::Device> devices;
		cl::Platform::getDefault().getDevices(CL_DEVICE_TYPE_GPU, &devices);
		if (devices.empty())
			throw std::runtime_error("No GPU found");

		_device = devices.front();
		_context = cl::Context(_device);
		std::string source = _getProgramSource(filename);
		cl::Program::Sources sources(1, std::make_pair(source.c_str(), source.size()));
		_program = cl::Program(_context, sources);

		if (_program.build({_device}) != CL_SUCCESS)
			throw std::runtime_error("Compile error: " + _program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(_device));
		_kernel = cl::Kernel(_program, kernel.data());
	}

	void ComputeShader::run(cl::NDRange global)
	{
		commands = cl::CommandQueue(_context, _device);
		commands.enqueueNDRangeKernel(_kernel, cl::NullRange, global);
	}
}
