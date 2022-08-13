#include "EZGL/ComputeShader.h"
#include <fstream>

namespace ezgl
{
	std::string ComputeShader::_getProgramSource(const std::vector<std::string>& filenames)
	{
		std::string source;
		for (const auto& filename : filenames)
		{
			std::ifstream file(filename);
			if (!file.good() || !file.is_open())
				throw std::runtime_error("Could not open kernel file: " + filename);
			std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			source += str;
		}
		return source;
	}

	ComputeShader::ComputeShader(const std::vector<std::string>& filenames, const std::string& kernel)
	{
		std::vector<cl::Device> devices;
		cl::Platform::getDefault().getDevices(CL_DEVICE_TYPE_GPU, &devices);
		if (devices.empty())
			throw std::runtime_error("No GPU found");

		_device = devices.front();
		_context = cl::Context(_device);
		std::string source = _getProgramSource(filenames);
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
