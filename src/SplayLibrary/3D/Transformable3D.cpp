///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Private/Private.hpp>

namespace spl
{
	Transformable3D::Transformable3D() :
		_translation(0.f, 0.f, 0.f),
		_rotation(1.f, 0.f, 0.f, 0.f),
		_scale(1.f, 1.f, 1.f)
	{
	}

	Transformable3D& Transformable3D::setTranslation(const vec3& translation)
	{
		_translation = translation;

		return *this;
	}

	Transformable3D& Transformable3D::move(const vec3& offset)
	{
		return setTranslation(_translation + offset);
	}

	Transformable3D& Transformable3D::setRotation(const scp::Quat<float>& rotation)
	{
		assert(std::abs(rotation.normSq() - 1.f) < 1e-2f);

		_rotation = rotation;
		return *this;
	}

	Transformable3D& Transformable3D::setRotation(const vec3& axis, float angle)
	{
		return setRotation(quaternionFromAxisAngle(axis, angle));
	}

	Transformable3D& Transformable3D::rotate(const scp::Quat<float>& rotation)
	{
		assert(std::abs(rotation.normSq() - 1.f) < 1e-4f);

		return setRotation(rotation * _rotation);
	}

	Transformable3D& Transformable3D::rotate(const vec3& axis, float angle)
	{
		return setRotation(quaternionFromAxisAngle(axis, angle) * _rotation);
	}

	Transformable3D& Transformable3D::setScale(const vec3& scale)
	{
		_scale = scale;

		return *this;
	}

	Transformable3D& Transformable3D::setScale(float scale)
	{
		return setScale({ scale, scale, scale });
	}

	Transformable3D& Transformable3D::scale(const vec3& scale)
	{
		return setScale(scale * _scale);
	}

	Transformable3D& Transformable3D::scale(float scale)
	{
		return setScale(vec3{scale, scale, scale} * _scale);
	}

	vec3 Transformable3D::applyTranslationTo(const vec3& vector) const
	{
		return vector + _translation;
	}

	vec3 Transformable3D::applyRotationTo(const vec3& vector) const
	{
		scp::Quat<float> v{ 0.f, vector.x, vector.y, vector.z };

		scp::Quat<float> inv = _rotation;
		inv.inverse();

		v = _rotation * v * inv;

		return vec3{ v.x, v.y, v.z };
	}

	vec3 Transformable3D::applyScaleTo(const vec3& vector) const
	{
		return vector * _scale;
	}

	vec3 Transformable3D::applyTransformTo(const vec3& vector) const
	{
		return applyTransformTo(applyRotationTo(applyScaleTo(vector)));
	}

	vec3 Transformable3D::applyInverseTranslationTo(const vec3& vector) const
	{
		return vector - _translation;
	}

	vec3 Transformable3D::applyInverseRotationTo(const vec3& vector) const
	{
		scp::Quat<float> v{ 0.f, vector.x, vector.y, vector.z };

		scp::Quat<float> inv = _rotation;
		inv.inverse();

		v = inv * v * _rotation;

		return normalize(vec3{ v.x, v.y, v.z });
	}

	vec3 Transformable3D::applyInverseScaleTo(const vec3& vector) const
	{
		return vector / _scale;
	}

	vec3 Transformable3D::applyInverseTransformTo(const vec3& vector) const
	{
		return applyInverseScaleTo(applyInverseRotationTo(applyInverseTranslationTo(vector)));
	}

	mat3 Transformable3D::getRotationMatrix() const
	{
		const float aa = _rotation.w * _rotation.w;
		const float bb = _rotation.x * _rotation.x;
		const float cc = _rotation.y * _rotation.y;
		const float dd = _rotation.z * _rotation.z;

		const float ab2 = 2.f * _rotation.w * _rotation.x;
		const float ac2 = 2.f * _rotation.w * _rotation.y;
		const float ad2 = 2.f * _rotation.w * _rotation.z;

		const float bc2 = 2.f * _rotation.x * _rotation.y;
		const float bd2 = 2.f * _rotation.x * _rotation.z;

		const float cd2 = 2.f * _rotation.y * _rotation.z;

		const float r11 = aa + bb - cc - dd;
		const float r12 = bc2 - ad2;
		const float r13 = ac2 + bd2;
		const float r21 = ad2 + bc2;
		const float r22 = aa - bb + cc - dd;
		const float r23 = cd2 - ab2;
		const float r31 = bd2 - ac2;
		const float r32 = ab2 + cd2;
		const float r33 = aa - bb - cc + dd;

		return {
			r11, r12, r13,
			r21, r22, r23,
			r31, r32, r33
		};
	}

	mat4 Transformable3D::getTransformMatrix() const
	{
		const float& tx = _translation.x;
		const float& ty = _translation.y;
		const float& tz = _translation.z;

		const float aa = _rotation.w * _rotation.w;
		const float bb = _rotation.x * _rotation.x;
		const float cc = _rotation.y * _rotation.y;
		const float dd = _rotation.z * _rotation.z;

		const float ab2 = 2.f * _rotation.w * _rotation.x;
		const float ac2 = 2.f * _rotation.w * _rotation.y;
		const float ad2 = 2.f * _rotation.w * _rotation.z;

		const float bc2 = 2.f * _rotation.x * _rotation.y;
		const float bd2 = 2.f * _rotation.x * _rotation.z;

		const float cd2 = 2.f * _rotation.y * _rotation.z;

		const float r11 = aa + bb - cc - dd;
		const float r12 = bc2 - ad2;
		const float r13 = ac2 + bd2;
		const float r21 = ad2 + bc2;
		const float r22 = aa - bb + cc - dd;
		const float r23 = cd2 - ab2;
		const float r31 = bd2 - ac2;
		const float r32 = ab2 + cd2;
		const float r33 = aa - bb - cc + dd;

		const float& sx = _scale.x;
		const float& sy = _scale.y;
		const float& sz = _scale.z;

		return {
			r11 * sx, r12 * sy, r13 * sz, tx,
			r21 * sx, r22 * sy, r23 * sz, ty,
			r31 * sx, r32 * sy, r33 * sz, tz,
			0.f     , 0.f     , 0.f     , 1.f
		};
	}

	mat3 Transformable3D::getInverseRotationMatrix() const
	{
		scp::Quat<float> rot = _rotation;
		rot.inverse();

		const float aa = rot.w * rot.w;
		const float bb = rot.x * rot.x;
		const float cc = rot.y * rot.y;
		const float dd = rot.z * rot.z;

		const float ab2 = 2.f * rot.w * rot.x;
		const float ac2 = 2.f * rot.w * rot.y;
		const float ad2 = 2.f * rot.w * rot.z;

		const float bc2 = 2.f * rot.x * rot.y;
		const float bd2 = 2.f * rot.x * rot.z;

		const float cd2 = 2.f * rot.y * rot.z;

		const float r11 = aa + bb - cc - dd;
		const float r12 = bc2 - ad2;
		const float r13 = ac2 + bd2;
		const float r21 = ad2 + bc2;
		const float r22 = aa - bb + cc - dd;
		const float r23 = cd2 - ab2;
		const float r31 = bd2 - ac2;
		const float r32 = ab2 + cd2;
		const float r33 = aa - bb - cc + dd;

		return {
			r11, r12, r13,
			r21, r22, r23,
			r31, r32, r33
		};
	}

	mat4 Transformable3D::getInverseTransformMatrix() const
	{
		const float sx = 1.f / _scale.x;
		const float sy = 1.f / _scale.y;
		const float sz = 1.f / _scale.z;

		scp::Quat<float> rot = _rotation;
		rot.inverse();

		const float aa = rot.w * rot.w;
		const float bb = rot.x * rot.x;
		const float cc = rot.y * rot.y;
		const float dd = rot.z * rot.z;

		const float ab2 = 2.f * rot.w * rot.x;
		const float ac2 = 2.f * rot.w * rot.y;
		const float ad2 = 2.f * rot.w * rot.z;

		const float bc2 = 2.f * rot.x * rot.y;
		const float bd2 = 2.f * rot.x * rot.z;

		const float cd2 = 2.f * rot.y * rot.z;

		const float r11 = sx * (aa + bb - cc - dd);
		const float r12 = sx * (bc2 - ad2);
		const float r13 = sx * (ac2 + bd2);
		const float r21 = sy * (ad2 + bc2);
		const float r22 = sy * (aa - bb + cc - dd);
		const float r23 = sy * (cd2 - ab2);
		const float r31 = sz * (bd2 - ac2);
		const float r32 = sz * (ab2 + cd2);
		const float r33 = sz * (aa - bb - cc + dd);

		const float tx = -_translation.x;
		const float ty = -_translation.y;
		const float tz = -_translation.z;

		return {
			r11, r12, r13, r11 * tx + r12 * ty + r13 * tz,
			r21, r22, r23, r21 * tx + r22 * ty + r23 * tz,
			r31, r32, r33, r31 * tx + r32 * ty + r33 * tz,
			0.f, 0.f, 0.f, 1.f
		};
	}

	const vec3& Transformable3D::getTranslation() const
	{
		return _translation;
	}

	const scp::Quat<float> Transformable3D::getRotation() const
	{
		return _rotation;
	}

	const vec3& Transformable3D::getScale() const
	{
		return _scale;
	}

	scp::Quat<float> Transformable3D::quaternionFromAxisAngle(const vec3& axis, float angle)
	{
		if (length(axis) == 0.f)
		{
			return { 1.f, 0.f, 0.f, 0.f };
		}

		const vec3 axisNorm = normalize(axis);
		const float halfAngle = angle / 2.f;
		const float sinHalfAngle = std::sin(halfAngle);

		return {
			std::cos(halfAngle),
			axisNorm.x * sinHalfAngle,
			axisNorm.y * sinHalfAngle,
			axisNorm.z * sinHalfAngle
		};
	}
}
