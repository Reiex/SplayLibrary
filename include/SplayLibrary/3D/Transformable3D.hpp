///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/3D/types.hpp>

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

			Transformable3D& setTranslation(const vec3& translation);
			Transformable3D& move(const vec3& offset);

			Transformable3D& setRotation(const scp::Quat<float>& rotation);
			Transformable3D& setRotation(const vec3& axis, float angle);
			Transformable3D& rotate(const scp::Quat<float>& rotation);
			Transformable3D& rotate(const vec3& axis, float angle);

			Transformable3D& setScale(const vec3& scale);
			Transformable3D& setScale(float scale);
			Transformable3D& scale(const vec3& scale);
			Transformable3D& scale(float scale);


			vec3 applyTranslationTo(const vec3& vector) const;
			vec3 applyRotationTo(const vec3& vector) const;
			vec3 applyScaleTo(const vec3& vector) const;
			vec3 applyTransformTo(const vec3& vector) const;

			vec3 applyInverseTranslationTo(const vec3& vector) const;
			vec3 applyInverseRotationTo(const vec3& vector) const;
			vec3 applyInverseScaleTo(const vec3& vector) const;
			vec3 applyInverseTransformTo(const vec3& vector) const;

			mat3 getRotationMatrix() const;
			mat4 getTransformMatrix() const;

			mat3 getInverseRotationMatrix() const;
			mat4 getInverseTransformMatrix() const;


			const vec3& getTranslation() const;
			const scp::Quat<float> getRotation() const;
			const vec3& getScale() const;

			~Transformable3D() = default;

		protected:

			static scp::Quat<float> quaternionFromAxisAngle(const vec3& axis, float angle);

		private:

			vec3 _translation;
			scp::Quat<float> _rotation;
			vec3 _scale;
	};
}
