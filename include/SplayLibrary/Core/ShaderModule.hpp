///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/Core/CoreTypes.hpp>

namespace spl
{
	enum class ShaderStage
	{
		Undefined,
		Vertex,
		TessellationControl,
		TessellationEvaluation,
		Geometry,
		Fragment,
		Compute
	};

	class ShaderModule
	{
		public:

			ShaderModule();
			ShaderModule(ShaderStage stage, const std::filesystem::path& glslFile);
			ShaderModule(ShaderStage stage, const char* source, uint32_t size);
			ShaderModule(ShaderStage stage, const char* const* sources, const uint32_t* sizes, uint32_t count);
			ShaderModule(ShaderStage stage, const std::filesystem::path& spirvFile, const char* entryPoint, const uint32_t* constantIndices, const void* constantValues, uint32_t specializationConstantsCount);
			ShaderModule(ShaderStage stage, const void* binary, uint32_t size, const char* entryPoint, const uint32_t* constantIndices, const void* constantValues, uint32_t specializationConstantsCount);
			ShaderModule(const ShaderModule& shader) = delete;
			ShaderModule(ShaderModule&& shader) = delete;

			ShaderModule& operator=(const ShaderModule& shader) = delete;
			ShaderModule& operator=(ShaderModule&& shader) = delete;

			bool compileGlsl(ShaderStage stage, const std::filesystem::path& glslFile);
			bool compileGlsl(ShaderStage stage, const char* source, uint32_t size);
			bool compileGlsl(ShaderStage stage, const char* const* sources, const uint32_t* sizes, uint32_t count);
			bool compileSpirV(ShaderStage stage, const std::filesystem::path& spirvFile, const char* entryPoint, const uint32_t* constantIndices, const void* constantValues, uint32_t specializationConstantsCount);
			bool compileSpirV(ShaderStage stage, const void* binary, uint32_t size, const char* entryPoint, const uint32_t* constantIndices, const void* constantValues, uint32_t specializationConstantsCount);

			uint32_t getHandle() const;
			bool isValid() const;

			~ShaderModule();

			static void releaseShaderCompiler();

		private:

			void _destroy();

			uint32_t _shader;
			ShaderStage _stage;
			int32_t _compileStatus;
	};
}
