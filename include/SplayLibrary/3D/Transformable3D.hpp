///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2021-2023
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/3D/3DTypes.hpp>

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

			Transformable3D& setTranslation(const scp::f32vec3& translation);
			Transformable3D& move(const scp::f32vec3& offset);

			Transformable3D& setRotation(const scp::Quat<float>& rotation);
			Transformable3D& setRotation(const scp::f32vec3& axis, float angle);
			Transformable3D& rotate(const scp::Quat<float>& rotation);
			Transformable3D& rotate(const scp::f32vec3& axis, float angle);

			Transformable3D& setScale(const scp::f32vec3& scale);
			Transformable3D& setScale(float scale);
			Transformable3D& scale(const scp::f32vec3& scale);
			Transformable3D& scale(float scale);


			scp::f32vec3 applyTranslationTo(const scp::f32vec3& vector) const;
			scp::f32vec3 applyRotationTo(const scp::f32vec3& vector) const;
			scp::f32vec3 applyScaleTo(const scp::f32vec3& vector) const;
			scp::f32vec3 applyTransformTo(const scp::f32vec3& vector) const;

			scp::f32vec3 applyInverseTranslationTo(const scp::f32vec3& vector) const;
			scp::f32vec3 applyInverseRotationTo(const scp::f32vec3& vector) const;
			scp::f32vec3 applyInverseScaleTo(const scp::f32vec3& vector) const;
			scp::f32vec3 applyInverseTransformTo(const scp::f32vec3& vector) const;

			scp::f32mat3x3 getRotationMatrix() const;
			scp::f32mat4x4 getTransformMatrix() const;

			scp::f32mat3x3 getInverseRotationMatrix() const;
			scp::f32mat4x4 getInverseTransformMatrix() const;


			const scp::f32vec3& getTranslation() const;
			const scp::Quat<float> getRotation() const;
			const scp::f32vec3& getScale() const;

			~Transformable3D() = default;

		protected:

			static scp::Quat<float> _quaternionFromAxisAngle(const scp::f32vec3& axis, float angle);

		private:

			scp::f32vec3 _translation;
			scp::Quat<float> _rotation;
			scp::f32vec3 _scale;
	};
}
