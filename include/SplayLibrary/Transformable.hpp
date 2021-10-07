#pragma once

#include <SplayLibrary/types.hpp>

namespace spl
{
	class Transformable
	{
		public:

			void setPosition(const vec3& position);
			void move(const vec3& vector);

			void setRotation(const scp::Quat<float>& rotation);
			void rotate(const vec3& axis, float angle);

			const mat4& getTransform() const;
			const mat4& getInverseTransform() const;

		private:

			vec3 _pos;
			scp::Quat<float> _rot;
			vec3 _scale;

			mutable mat4 _transform;
			mutable mat4 _inverseTransform;
	};
}
