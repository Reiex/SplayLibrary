///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/Core/types.hpp>

namespace spl
{
	class Shader
	{
		public:

			Shader(const std::string& vertex, const std::string& fragment);
			Shader(const std::string& vertex, const std::string& geometry, const std::string& fragment);
			Shader(const std::string& vertex, const std::string& tessellationControl, const std::string& tessellationEvaluation, const std::string& geometry, const std::string& fragment);
			Shader(const Shader& shader) = delete;
			Shader(Shader&& shader) = delete;

			Shader& operator=(const Shader& shader) = delete;
			Shader& operator=(Shader&& shader) = delete;

			void setUniform(const std::string& location, float value);
			void setUniform(const std::string& location, const scp::f32vec2& value);
			void setUniform(const std::string& location, const scp::f32vec3& value);
			void setUniform(const std::string& location, const scp::f32vec4& value);
			void setUniform(const std::string& location, const float* values, uint32_t count);
			void setUniform(const std::string& location, const scp::f32vec2* values, uint32_t count);
			void setUniform(const std::string& location, const scp::f32vec3* values, uint32_t count);
			void setUniform(const std::string& location, const scp::f32vec4* values, uint32_t count);

			void setUniform(const std::string& location, const int32_t value);
			void setUniform(const std::string& location, const scp::i32vec2& value);
			void setUniform(const std::string& location, const scp::i32vec3& value);
			void setUniform(const std::string& location, const scp::i32vec4& value);
			void setUniform(const std::string& location, const int32_t* values, uint32_t count);
			void setUniform(const std::string& location, const scp::i32vec2* values, uint32_t count);
			void setUniform(const std::string& location, const scp::i32vec3* values, uint32_t count);
			void setUniform(const std::string& location, const scp::i32vec4* values, uint32_t count);

			void setUniform(const std::string& location, uint32_t value);
			void setUniform(const std::string& location, const scp::u32vec2& value);
			void setUniform(const std::string& location, const scp::u32vec3& value);
			void setUniform(const std::string& location, const scp::u32vec4& value);
			void setUniform(const std::string& location, const uint32_t* values, uint32_t count);
			void setUniform(const std::string& location, const scp::u32vec2* values, uint32_t count);
			void setUniform(const std::string& location, const scp::u32vec3* values, uint32_t count);
			void setUniform(const std::string& location, const scp::u32vec4* values, uint32_t count);

			void setUniform(const std::string& location, const scp::f32mat2x2& value);
			void setUniform(const std::string& location, const scp::f32mat2x3& value);
			void setUniform(const std::string& location, const scp::f32mat2x4& value);
			void setUniform(const std::string& location, const scp::f32mat3x2& value);
			void setUniform(const std::string& location, const scp::f32mat3x3& value);
			void setUniform(const std::string& location, const scp::f32mat3x4& value);
			void setUniform(const std::string& location, const scp::f32mat4x2& value);
			void setUniform(const std::string& location, const scp::f32mat4x3& value);
			void setUniform(const std::string& location, const scp::f32mat4x4& value);

			void setUniform(const std::string& location, const scp::f32mat2x2* value, uint32_t count);
			void setUniform(const std::string& location, const scp::f32mat2x3* value, uint32_t count);
			void setUniform(const std::string& location, const scp::f32mat2x4* value, uint32_t count);
			void setUniform(const std::string& location, const scp::f32mat3x2* value, uint32_t count);
			void setUniform(const std::string& location, const scp::f32mat3x3* value, uint32_t count);
			void setUniform(const std::string& location, const scp::f32mat3x4* value, uint32_t count);
			void setUniform(const std::string& location, const scp::f32mat4x2* value, uint32_t count);
			void setUniform(const std::string& location, const scp::f32mat4x3* value, uint32_t count);
			void setUniform(const std::string& location, const scp::f32mat4x4* value, uint32_t count);

			void setUniform(const std::string& location, const RawTexture& texture, uint32_t textureUnit = 0);
			void setUniform(const std::string& location, const TextureBase& texture, uint32_t textureUnit = 0);

			bool isValid() const;
			uint32_t getHandle() const;

			static void bind(const Shader& shader);
			static void unbind();

			~Shader();

		private:

			Shader();

			template<typename TFunc, typename... TArgs>
			void _setUniform(const TFunc& func, const std::string& location, const TArgs&... args);

			int32_t _getUniformLocation(const std::string& location);

			uint32_t _program;
			std::unordered_map<std::string, int32_t> _uniformLocations;
	};
}

#include <SplayLibrary/Core/templates/Shader.hpp>
