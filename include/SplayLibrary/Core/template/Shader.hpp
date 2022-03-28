#pragma once

#include <SplayLibrary/Core/Shader.hpp>

namespace spl
{
	template<typename TFunc, typename... TArgs>
	void Shader::setUniform(const TFunc& func, const std::string& location, const TArgs&... args)
	{
		func(getUniformLocation(location), args...);
	}
}
