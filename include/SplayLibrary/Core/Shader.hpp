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
			void setUniform(const std::string& location, const vec2& value);
			void setUniform(const std::string& location, const vec3& value);
			void setUniform(const std::string& location, const vec4& value);
			void setUniform(const std::string& location, const float* values, uint32_t count);
			void setUniform(const std::string& location, const vec2* values, uint32_t count);
			void setUniform(const std::string& location, const vec3* values, uint32_t count);
			void setUniform(const std::string& location, const vec4* values, uint32_t count);

			void setUniform(const std::string& location, const int32_t value);
			void setUniform(const std::string& location, const ivec2& value);
			void setUniform(const std::string& location, const ivec3& value);
			void setUniform(const std::string& location, const ivec4& value);
			void setUniform(const std::string& location, const int32_t* values, uint32_t count);
			void setUniform(const std::string& location, const ivec2* values, uint32_t count);
			void setUniform(const std::string& location, const ivec3* values, uint32_t count);
			void setUniform(const std::string& location, const ivec4* values, uint32_t count);

			void setUniform(const std::string& location, uint32_t value);
			void setUniform(const std::string& location, const uvec2& value);
			void setUniform(const std::string& location, const uvec3& value);
			void setUniform(const std::string& location, const uvec4& value);
			void setUniform(const std::string& location, const uint32_t* values, uint32_t count);
			void setUniform(const std::string& location, const uvec2* values, uint32_t count);
			void setUniform(const std::string& location, const uvec3* values, uint32_t count);
			void setUniform(const std::string& location, const uvec4* values, uint32_t count);

			void setUniform(const std::string& location, const mat2& value);
			void setUniform(const std::string& location, const mat2x3& value);
			void setUniform(const std::string& location, const mat2x4& value);
			void setUniform(const std::string& location, const mat3x2& value);
			void setUniform(const std::string& location, const mat3& value);
			void setUniform(const std::string& location, const mat3x4& value);
			void setUniform(const std::string& location, const mat4x2& value);
			void setUniform(const std::string& location, const mat4x3& value);
			void setUniform(const std::string& location, const mat4& value);

			void setUniform(const std::string& location, const mat2* value, uint32_t count);
			void setUniform(const std::string& location, const mat2x3* value, uint32_t count);
			void setUniform(const std::string& location, const mat2x4* value, uint32_t count);
			void setUniform(const std::string& location, const mat3x2* value, uint32_t count);
			void setUniform(const std::string& location, const mat3* value, uint32_t count);
			void setUniform(const std::string& location, const mat3x4* value, uint32_t count);
			void setUniform(const std::string& location, const mat4x2* value, uint32_t count);
			void setUniform(const std::string& location, const mat4x3* value, uint32_t count);
			void setUniform(const std::string& location, const mat4* value, uint32_t count);

			void setUniform(const std::string& location, const RawTexture& texture, uint32_t textureUnit = 0);
			void setUniform(const std::string& location, const TextureBase& texture, uint32_t textureUnit = 0);

			bool isValid() const;
			uint32_t getHandle() const;

			static void bind(const Shader& shader);
			static void unbind();

			~Shader();

		private:

			template<typename TFunc, typename... TArgs>
			void setUniform(const TFunc& func, const std::string& location, const TArgs&... args);

			Shader();

			int32_t getUniformLocation(const std::string& location);

			uint32_t _program;
			std::unordered_map<std::string, int32_t> _uniformLocations;
	};
}

#include <SplayLibrary/Core/template/Shader.hpp>
