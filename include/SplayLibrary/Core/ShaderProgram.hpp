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
	class ShaderProgram
	{
		public:

			ShaderProgram();
			ShaderProgram(const ShaderProgram& program) = delete;
			ShaderProgram(ShaderProgram&& program) = delete;

			ShaderProgram& operator=(const ShaderProgram& program) = delete;
			ShaderProgram& operator=(ShaderProgram&& program) = delete;

			~ShaderProgram();

		private:

			uint32_t _program;
			std::vector<const ShaderModule*> _modules;
	};
}
