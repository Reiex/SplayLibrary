#pragma once

#include <SplayLibrary/3D/types.hpp>

#include <SplayLibrary/Core/Glsl.hpp>

namespace spl
{
	class Transformable3D
	{
		public:

			Transformable3D();
			Transformable3D(const Transformable3D& transformable) = default;
			Transformable3D(Transformable3D&& transformable) = default;

			Transformable3D& operator=(const Transformable3D& transformable) = default;
			Transformable3D& operator=(Transformable3D&& transformable) = default;

			Transformable3D& setPosition(const vec3& position);
			Transformable3D& move(const vec3& offset);

			Transformable3D& setRotation(const scp::Quat<float>& rotation);
			Transformable3D& setRotation(const vec3& axis, float angle);
			Transformable3D& rotate(const scp::Quat<float>& rotation);
			Transformable3D& rotate(const vec3& axis, float angle);

			Transformable3D& setScale(const vec3& scale);
			Transformable3D& setScale(float scale);
			Transformable3D& scale(const vec3& scale);
			Transformable3D& scale(float scale);

			const vec3& getPosition() const;
			const scp::Quat<float> getRotation() const;
			const vec3& getScale() const;
			const mat4& getTransformMatrix() const;
			const mat4& getInverseTransformMatrix() const;

			~Transformable3D() = default;

		private:

			void computeTransformMatrix() const;
			void computeInverseTransformMatrix() const;

			vec3 _position;
			scp::Quat<float> _rotation;
			vec3 _scale;

			mutable bool _updateTransformMatrix;
			mutable mat4 _transformMatrix;
			mutable bool _updateInverseTransformMatrix;
			mutable mat4 _inverseTransformMatrix;
	};
}
