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
	template<CGenType TValue> void ShaderProgram::setUniform(const std::string& name, const TValue& value) const
	{
		static constexpr GlslType type = _spl::genTypeToGlslType<TValue>();
		
		if constexpr (type == GlslType::Bool)
		{
			int32_t buffer = value;
			_setUniform(name, GlslType::Int, &buffer, 1);
		}
		else if constexpr (type == GlslType::BoolVec2)
		{
			int32_t buffer[2] = { value.x, value.y };
			_setUniform(name, GlslType::IntVec2, buffer, 1);
		}
		else if constexpr (type == GlslType::BoolVec3)
		{
			int32_t buffer[3] = { value.x, value.y, value.z };
			_setUniform(name, GlslType::IntVec3, buffer, 1);
		}
		else if constexpr (type == GlslType::BoolVec4)
		{
			int32_t buffer[4] = { value.x, value.y, value.z, value.w };
			_setUniform(name, GlslType::IntVec4, buffer, 1);
		}
		else
		{
			_setUniform(name, type, &value, 1);
		}
	}

	template<CGenType TValue> void ShaderProgram::setUniform(const std::string& name, const TValue* values, uint32_t count) const
	{
		static constexpr GlslType type = _spl::genTypeToGlslType<TValue>();

		if constexpr (type == GlslType::Bool)
		{
			std::vector<int32_t> buffer(count);
			std::copy_n(values, count, buffer.begin());

			_setUniform(name, GlslType::Int, buffer.data(), count);
		}
		else if constexpr (type == GlslType::BoolVec2)
		{
			std::vector<int32_t> buffer(2 * count);
			std::copy_n(reinterpret_cast<const bool*>(values), 2 * count, buffer.begin());

			_setUniform(name, GlslType::IntVec2, buffer.data(), count);
		}
		else if constexpr (type == GlslType::BoolVec3)
		{
			std::vector<int32_t> buffer(3 * count);
			std::copy_n(reinterpret_cast<const bool*>(values), 3 * count, buffer.begin());

			_setUniform(name, GlslType::IntVec3, buffer.data(), count);
		}
		else if constexpr (type == GlslType::BoolVec4)
		{
			std::vector<int32_t> buffer(4 * count);
			std::copy_n(reinterpret_cast<const bool*>(values), 4 * count, buffer.begin());

			_setUniform(name, GlslType::IntVec4, buffer.data(), count);
		}
		else
		{
			_setUniform(name, type, values, count);
		}
	}

	template<scp::CMat TMat> void ShaderProgram::setUniform(const std::string& name, const TMat& matrix) const
	{
		static constexpr GlslType type = _spl::matTypeToGlslType<TMat>();
		_setUniform(name, type, &matrix, 1);
	}

	template<scp::CMat TMat> void ShaderProgram::setUniform(const std::string& name, const TMat* matrices, uint32_t count) const
	{
		static constexpr GlslType type = _spl::matTypeToGlslType<TMat>();
		_setUniform(name, type, matrices, count);
	}
}
