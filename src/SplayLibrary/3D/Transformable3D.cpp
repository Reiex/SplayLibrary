#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Core/Private.hpp>

namespace spl
{
	Transformable3D::Transformable3D() :
		_position(0.f, 0.f, 0.f),
		_rotation(1.f, 0.f, 0.f, 0.f),
		_scale(1.f, 1.f, 1.f),
		_updateTransformMatrix(false),
		_transformMatrix(
			{
				1.f, 0.f, 0.f, 0.f,
				0.f, 1.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f
			}
		),
		_updateInverseTransformMatrix(false),
		_inverseTransformMatrix(
			{
				1.f, 0.f, 0.f, 0.f,
				0.f, 1.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f
			}
		)
	{
	}

	Transformable3D& Transformable3D::setPosition(const vec3& position)
	{
		_position = position;
		_updateTransformMatrix = true;
		_updateInverseTransformMatrix = true;

		return *this;
	}

	Transformable3D& Transformable3D::move(const vec3& offset)
	{
		return setPosition(_position + offset);
	}

	Transformable3D& Transformable3D::setRotation(const scp::Quat<float>& rotation)
	{
		assert(std::abs(rotation.normSq() - 1.f) < 1e-2f);

		_rotation = rotation;
		_updateTransformMatrix = true;
		_updateInverseTransformMatrix = true;

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
		_updateTransformMatrix = true;
		_updateInverseTransformMatrix = true;

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
		return vector + _position;
	}

	vec3 Transformable3D::applyRotationTo(const vec3& vector) const
	{
		scp::Quat<float> v{ 0.f, vector.x, vector.y, vector.z };
		v = _rotation * v * _rotation.inverse();

		return normalize(vec3{ v.b, v.c, v.d });
	}

	vec3 Transformable3D::applyScaleTo(const vec3& vector) const
	{
		return vector / _scale;
	}

	vec3 Transformable3D::applyTransformTo(const vec3& vector) const
	{
		return applyTransformTo(applyRotationTo(applyScaleTo(vector)));
	}

	const vec3& Transformable3D::getPosition() const
	{
		return _position;
	}

	const scp::Quat<float> Transformable3D::getRotation() const
	{
		return _rotation;
	}

	const vec3& Transformable3D::getScale() const
	{
		return _scale;
	}

	const mat4& Transformable3D::getTransformMatrix() const
	{
		computeTransformMatrix();
		return _transformMatrix;
	}

	const mat4& Transformable3D::getInverseTransformMatrix() const
	{
		computeInverseTransformMatrix();
		return _inverseTransformMatrix;
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

	void Transformable3D::computeTransformMatrix() const
	{
		if (_updateTransformMatrix)
		{
			const float& tx = _position.x;
			const float& ty = _position.y;
			const float& tz = _position.z;

			const float aa = _rotation.a * _rotation.a;
			const float bb = _rotation.b * _rotation.b;
			const float cc = _rotation.c * _rotation.c;
			const float dd = _rotation.d * _rotation.d;

			const float ab2 = 2.f * _rotation.a * _rotation.b;
			const float ac2 = 2.f * _rotation.a * _rotation.c;
			const float ad2 = 2.f * _rotation.a * _rotation.d;

			const float bc2 = 2.f * _rotation.b * _rotation.c;
			const float bd2 = 2.f * _rotation.b * _rotation.d;

			const float cd2 = 2.f * _rotation.c * _rotation.d;

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

			_transformMatrix = {
				r11 * sx, r12 * sy, r13 * sz, tx,
				r21 * sx, r22 * sy, r23 * sz, ty,
				r31 * sx, r32 * sy, r33 * sz, tz,
				0.f     , 0.f     , 0.f     , 1.f
			};

			_updateTransformMatrix = false;
		}
	}

	void Transformable3D::computeInverseTransformMatrix() const
	{
		if (_updateInverseTransformMatrix)
		{
			const float sx = 1.f / _scale.x;
			const float sy = 1.f / _scale.y;
			const float sz = 1.f / _scale.z;

			scp::Quat<float> rot = _rotation.inverse();

			const float aa = rot.a * rot.a;
			const float bb = rot.b * rot.b;
			const float cc = rot.c * rot.c;
			const float dd = rot.d * rot.d;

			const float ab2 = 2.f * rot.a * rot.b;
			const float ac2 = 2.f * rot.a * rot.c;
			const float ad2 = 2.f * rot.a * rot.d;

			const float bc2 = 2.f * rot.b * rot.c;
			const float bd2 = 2.f * rot.b * rot.d;

			const float cd2 = 2.f * rot.c * rot.d;

			const float r11 = aa + bb - cc - dd;
			const float r12 = bc2 - ad2;
			const float r13 = ac2 + bd2;
			const float r21 = ad2 + bc2;
			const float r22 = aa - bb + cc - dd;
			const float r23 = cd2 - ab2;
			const float r31 = bd2 - ac2;
			const float r32 = ab2 + cd2;
			const float r33 = aa - bb - cc + dd;

			const float tx = -_position.x;
			const float ty = -_position.y;
			const float tz = -_position.z;

			_inverseTransformMatrix = {
				r11 * sx, r12 * sx, r13 * sx, sx*(r11*tx + r12*ty + r13*tz),
				r21 * sy, r22 * sy, r23 * sy, sy*(r21*tx + r22*ty + r23*tz),
				r31 * sz, r32 * sz, r33 * sz, sz*(r31*tx + r32*ty + r33*tz),
				0.f     , 0.f     , 0.f     , 1.f
			};

			_updateInverseTransformMatrix = false;
		}
	}
}
