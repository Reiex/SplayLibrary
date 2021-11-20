#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Core/Private.hpp>

namespace spl
{
	namespace
	{
		scp::Quat<float> quatFromAxisAngle(const vec3& axis, float angle)
		{
			const vec3 axisNorm = normalize(axis);
			const float halfAngle = angle / 2.f;
			const float sinHalfAngle = std::sin(halfAngle);

			return {
				std::cos(angle / 2.f),
				axisNorm.x * sinHalfAngle,
				axisNorm.y * sinHalfAngle,
				axisNorm.z * sinHalfAngle
			};
		}
	}

	Transformable::Transformable() :
		_position(0.f, 0.f, 0.f),
		_rotation(1.f, 0.f, 0.f, 0.f),
		_scale(1.f, 1.f, 1.f),
		_updateTransform(false),
		_transform({1.f, 0.f, 0.f, 0.f,
					0.f, 1.f, 0.f, 0.f,
					0.f, 0.f, 1.f, 0.f,
					0.f, 0.f, 0.f, 1.f})
	{
	}

	Transformable& Transformable::setPosition(const vec3& position)
	{
		_position = position;
		_updateTransform = true;

		return *this;
	}

	Transformable& Transformable::move(const vec3& offset)
	{
		return setPosition(_position + offset);
	}

	Transformable& Transformable::setRotation(const scp::Quat<float>& rotation)
	{
		assert(std::abs(rotation.normSq() - 1.f) < 1e-2f);

		_rotation = rotation;
		_updateTransform = true;

		return *this;
	}

	Transformable& Transformable::setRotation(const vec3& axis, float angle)
	{
		return setRotation(quatFromAxisAngle(axis, angle));
	}

	Transformable& Transformable::rotate(const scp::Quat<float>& rotation)
	{
		assert(std::abs(rotation.normSq() - 1.f) < 1e-4f);

		return setRotation(rotation * _rotation);
	}

	Transformable& Transformable::rotate(const vec3& axis, float angle)
	{
		return setRotation(quatFromAxisAngle(axis, angle) * _rotation);
	}

	Transformable& Transformable::setScale(const vec3& scale)
	{
		_scale = scale;
		_updateTransform = true;

		return *this;
	}

	Transformable& Transformable::setScale(float scale)
	{
		return setScale({ scale, scale, scale });
	}

	Transformable& Transformable::scale(const vec3& scale)
	{
		return setScale(scale * _scale);
	}

	Transformable& Transformable::scale(float scale)
	{
		return setScale(vec3{scale, scale, scale} * _scale);
	}

	const vec3& Transformable::getPosition() const
	{
		return _position;
	}

	const scp::Quat<float> Transformable::getRotation() const
	{
		return _rotation;
	}

	const vec3& Transformable::getScale() const
	{
		return _scale;
	}

	const mat4& Transformable::getMatrix() const
	{
		computeMatrices();
		return _transform;
	}

	void Transformable::computeMatrices() const
	{
		if (_updateTransform)
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

			_transform = {
				r11 * sx, r12 * sx, r13 * sx, tx,
				r21 * sy, r22 * sy, r23 * sy, ty,
				r31 * sz, r32 * sz, r33 * sz, tz,
				0.f     , 0.f     , 0.f     , 1.f
			};

			_updateTransform = false;
		}
	}
}
