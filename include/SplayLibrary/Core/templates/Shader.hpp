///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/Core/CoreDecl.hpp>
#include <SplayLibrary/Private/PrivateIncluded.hpp>

namespace spl
{
	template<typename TFunc, typename... TArgs>
	void Shader::_setUniform(const TFunc& func, const std::string& location, const TArgs&... args)
	{
		func(_getUniformLocation(location), args...);
	}
}
