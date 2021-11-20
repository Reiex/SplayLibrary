#pragma once

#include <SplayLibrary/Core/types.hpp>

#include <SplayLibrary/Core/Glsl.hpp>

namespace spl
{
	class Transformable
	{
		public:

			Transformable();

			Transformable& setPosition(const vec3& position);
			Transformable& move(const vec3& offset);

			Transformable& setRotation(const scp::Quat<float>& rotation);
			Transformable& setRotation(const vec3& axis, float angle);
			Transformable& rotate(const scp::Quat<float>& rotation);
			Transformable& rotate(const vec3& axis, float angle);

			Transformable& setScale(const vec3& scale);
			Transformable& setScale(float scale);
			Transformable& scale(const vec3& scale);
			Transformable& scale(float scale);

			const vec3& getPosition() const;
			const scp::Quat<float> getRotation() const;
			const vec3& getScale() const;
			const mat4& getMatrix() const;

		private:

			void computeMatrices() const;

			vec3 _position;
			scp::Quat<float> _rotation;
			vec3 _scale;

			mutable bool _updateTransform;
			mutable mat4 _transform;
	};
}
