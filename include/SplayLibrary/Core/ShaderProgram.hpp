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
	namespace ShaderProgramFlags
	{
		enum Flags
		{
			None				= 0,
			Separable			= 1 << 0,
			BinaryRetrievable	= 1 << 1
		};
	}

	enum class ShaderProgramInterface
	{
		Uniform,
		UniformBlock,
		AtomicCounterBuffer,
		ProgramInput,
		ProgramOutput,
		TransformFeedbackVarying,
		TransformFeedbackBuffer,
		BufferVariable,
		ShaderStorageBlock,

		ComputeSubroutine,
		VertexSubroutine,
		TessControlSubroutine,
		TessEvalSubroutine,
		GeometrySubroutine,
		FragmentSubroutine,

		ComputeSubroutineUniform,
		VertexSubroutineUniform,
		TessControlSubroutineUniform,
		TessEvalSubroutineUniform,
		GeometrySubroutineUniform,
		FragmentSubroutineUniform
	};

	enum class ShaderProgramInterfaceInfo
	{
		ActiveResources,
		MaxNameLength,
		MaxNumActiveVariables,
		MaxNumCompatibleSubroutines
	};

	class ShaderProgram
	{
		public:

			ShaderProgram();
			ShaderProgram(const std::filesystem::path& glslCompute, ShaderProgramFlags::Flags flags = ShaderProgramFlags::None);
			ShaderProgram(const std::filesystem::path& glslVertex, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags = ShaderProgramFlags::None);
			ShaderProgram(const std::filesystem::path& glslVertex, const std::filesystem::path& glslGeometry, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags = ShaderProgramFlags::None);
			ShaderProgram(const std::filesystem::path& glslVertex, const std::filesystem::path& glslTessControl, const std::filesystem::path& glslTessEval, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags = ShaderProgramFlags::None);
			ShaderProgram(const std::filesystem::path& glslVertex, const std::filesystem::path& glslTessControl, const std::filesystem::path& glslTessEval, const std::filesystem::path& glslGeometry, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags = ShaderProgramFlags::None);
			ShaderProgram(const ShaderModule* shaders, uint8_t count, ShaderProgramFlags::Flags flags = ShaderProgramFlags::None);
			ShaderProgram(const ShaderProgram& program) = delete;
			ShaderProgram(ShaderProgram&& program) = delete;

			ShaderProgram& operator=(const ShaderProgram& program) = delete;
			ShaderProgram& operator=(ShaderProgram&& program) = delete;


			bool createFromGlsl(const std::filesystem::path& glslCompute, ShaderProgramFlags::Flags flags = ShaderProgramFlags::None);
			bool createFromGlsl(const std::filesystem::path& glslVertex, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags = ShaderProgramFlags::None);
			bool createFromGlsl(const std::filesystem::path& glslVertex, const std::filesystem::path& glslGeometry, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags = ShaderProgramFlags::None);
			bool createFromGlsl(const std::filesystem::path& glslVertex, const std::filesystem::path& glslTessControl, const std::filesystem::path& glslTessEval, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags = ShaderProgramFlags::None);
			bool createFromGlsl(const std::filesystem::path& glslVertex, const std::filesystem::path& glslTessControl, const std::filesystem::path& glslTessEval, const std::filesystem::path& glslGeometry, const std::filesystem::path& glslFragment, ShaderProgramFlags::Flags flags = ShaderProgramFlags::None);
			bool createFromShaderModules(const ShaderModule* shaders, uint8_t count, ShaderProgramFlags::Flags = ShaderProgramFlags::None);
			
			// TODO: Handle binary with a new class "ShaderBinary"

			uint32_t getInterfaceInfo(ShaderProgramInterface programInterface, ShaderProgramInterfaceInfo info) const;

			uint32_t getResourceIndex(ShaderProgramInterface programInterface, const std::string& name) const;
			void getResourceName(ShaderProgramInterface programInterface, uint32_t index, std::string& name, uint32_t nameBufferSize = 256) const;
			// glGetProgramResourceiv
			uint32_t getResourceLocation(ShaderProgramInterface programInterface, const std::string& name) const;
			uint32_t getResourceFragmentColorIndex(const std::string& name) const;

			void destroy();


			uint32_t getHandle() const;
			ShaderProgramFlags::Flags getFlags() const;
			bool isValid() const;


			~ShaderProgram();


			static void bind(const ShaderProgram& program);
			static void unbind();

		private:

			uint32_t _program;
			ShaderProgramFlags::Flags _flags;
			int32_t _linkStatus;
	};
}
