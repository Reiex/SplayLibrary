#include <SplayLibrary/SplayLibrary.hpp>
#include <SplayLibrary/Core/Private.hpp>

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
		assert(scp::pi > _fov && _fov > 0.f);
	}

	PerspectiveCamera::PerspectiveCamera(const uvec2& resolution, float near, float far, float fov) : PerspectiveCamera(static_cast<float>(resolution.x) / resolution.y, near, far, fov)
	{
	}

	void PerspectiveCamera::setAspect(float aspect)
	{
		_aspect = aspect;
		_updateProjectionMatrix = true;
	}

	void PerspectiveCamera::setAspect(const uvec2& resolution)
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

	float PerspectiveCamera::getAspect() const
	{
		return _aspect;
	}

	const vec2& PerspectiveCamera::getFOV() const
	{
		return _fov;
	}

	float PerspectiveCamera::getNearDistance() const
	{
		return _near;
	}

	float PerspectiveCamera::getFarDistance() const
	{
		return _far;
	}

	const mat4& PerspectiveCamera::getViewMatrix() const
	{
		return getInverseTransformMatrix();
	}

	const mat4& PerspectiveCamera::getProjectionMatrix() const
	{
		computeProjectionMatrix();
		return _projectionMatrix;
	}

	void PerspectiveCamera::computeProjectionMatrix() const
	{
		if (_updateProjectionMatrix)
		{
			const float invTanFov = 1.f / std::tan(_fov / 2.f);
			const float a = invTanFov / _aspect;
			const float b = invTanFov;
			const float c = -(_near + _far) / (_near - _far);
			const float d = (2.f * _near * _far) / (_near - _far);

			_projectionMatrix = {
				a  , 0.f, 0.f, 0.f,
				0.f, b  , 0.f, 0.f,
				0.f, 0.f, c  , d  ,
				0.f, 0.f, 1.f, 0.f
			};

			_updateProjectionMatrix = false;
		}
	}
}
