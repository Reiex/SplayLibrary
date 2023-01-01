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
	PerspectiveCamera::PerspectiveCamera(float aspect, float near, float far, float fov) : Transformable3D(),
		_aspect(aspect),
		_near(near),
		_far(far),
		_fov(fov),
		_updateProjectionMatrix(true),
		_projectionMatrix(
			{
				1.f, 0.f, 0.f, 0.f,
				0.f, 1.f, 0.f, 0.f,
				0.f, 0.f, 1.f, 0.f,
				0.f, 0.f, 0.f, 1.f
			}
		)
	{
		assert(_aspect > 0.f && !std::isinf(_aspect));
		assert(_far > _near && _near > 0.f);
		assert(std::numbers::pi > _fov && _fov > 0.f);
	}

	PerspectiveCamera::PerspectiveCamera(const scp::u32vec2& resolution, float near, float far, float fov) : PerspectiveCamera(static_cast<float>(resolution.x) / resolution.y, near, far, fov)
	{
	}

	void PerspectiveCamera::setAspect(float aspect)
	{
		_aspect = aspect;
		_updateProjectionMatrix = true;
	}

	void PerspectiveCamera::setAspect(const scp::u32vec2& resolution)
	{
		setAspect(static_cast<float>(resolution.x) / resolution.y);
	}

	void PerspectiveCamera::setFOV(float fov)
	{
		_fov = fov;
		_updateProjectionMatrix = true;
	}

	void PerspectiveCamera::setNearDistance(float near)
	{
		_near = near;
		_updateProjectionMatrix = true;
	}

	void PerspectiveCamera::setFarDistance(float far)
	{
		_far = far;
		_updateProjectionMatrix = true;
	}

	void PerspectiveCamera::lookAt(const scp::f32vec3& position, float dutchAngle)
	{
		if (distance(position, getTranslation()) == 0.f)
		{
			return;
		}

		scp::Quat<float> rot = { 1.f, 0.f, 0.f, 0.f };
		setRotation(rot);

		scp::f32vec3 dir = normalize(position - getTranslation());

		scp::f32vec3 dirPlane = { dir.x, 0.f, dir.z };
		if (scp::length(dirPlane) != 0.f)
		{
			const float angle = std::atan2(-dirPlane.x, -dirPlane.z);

			rotate(getUpVector(), angle);
		}

		dirPlane = { 0.f, dir.y, dir.z };
		if (scp::length(dirPlane) != 0.f)
		{
			const float angle = std::numbers::pi / 2 - std::acos(dot(dirPlane, { 0.f, 1.f, 0.f }));

			rotate(-getLeftVector(), angle);
		}

		if (dutchAngle != 0.f)
		{
			rotate(getFrontVector(), dutchAngle);
		}
	}

	float PerspectiveCamera::getAspect() const
	{
		return _aspect;
	}

	float PerspectiveCamera::getNearDistance() const
	{
		return _near;
	}

	float PerspectiveCamera::getFarDistance() const
	{
		return _far;
	}

	scp::f32vec3 PerspectiveCamera::getUpVector() const
	{
		return applyRotationTo({ 0.f, 1.f, 0.f });
	}

	scp::f32vec3 PerspectiveCamera::getFrontVector() const
	{
		return applyRotationTo({ 0.f, 0.f, -1.f });
	}

	scp::f32vec3 PerspectiveCamera::getLeftVector() const
	{
		return applyRotationTo({ -1.f, 0.f, 0.f });
	}

	scp::f32mat4x4 PerspectiveCamera::getViewMatrix() const
	{
		return getInverseTransformMatrix();
	}

	const scp::f32mat4x4& PerspectiveCamera::getProjectionMatrix() const
	{
		_computeProjectionMatrix();
		return _projectionMatrix;
	}

	void PerspectiveCamera::_computeProjectionMatrix() const
	{
		if (_updateProjectionMatrix)
		{
			const float invTanFov = 1.f / std::tan(_fov / 2.f);
			const float a = invTanFov / _aspect;
			const float b = invTanFov;
			const float c = (_near + _far) / (_near - _far);
			const float d = (2.f * _near * _far) / (_near - _far);

			_projectionMatrix = {
				a  , 0.f,  0.f, 0.f,
				0.f, b  ,  0.f, 0.f,
				0.f, 0.f,  c  , d  ,
				0.f, 0.f, -1.f, 0.f
			};

			_updateProjectionMatrix = false;
		}
	}
}
