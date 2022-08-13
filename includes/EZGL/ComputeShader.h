#pragma once

#include <string>
#include <vector>
#include <CL/cl.hpp>

namespace ezgl
{
	class ComputeShader
	{
	protected:
		cl::Device _device;
		cl::Context _context;
		cl::Kernel _kernel;
		cl::Program _program;

	public:
		cl::CommandQueue commands;

	private:
		std::string _getProgramSource(const std::vector<std::string>& filenames);

	public:
		ComputeShader() = default;
		ComputeShader(const ComputeShader& other) = default;
		ComputeShader(const std::vector<std::string>& filenames, const std::string& kernel);
		ComputeShader& operator=(const ComputeShader& other) = default;

		template<typename T> cl::Buffer createBuffer(cl_mem_flags flags, std::vector<T>& buffer)
		{
			return cl::Buffer(_context, flags, buffer.size() * sizeof(T), buffer.data());
		}

		template<typename T> void setArg(cl_uint index, const T& value) { _kernel.setArg(index, value); }

		void run(cl::NDRange global);
	};
}
