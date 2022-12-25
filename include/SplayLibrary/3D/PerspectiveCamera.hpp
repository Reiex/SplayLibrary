///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//! \file
//! \author Reiex
//! \copyright The MIT License (MIT)
//! \date 2019-2022
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SplayLibrary/3D/types.hpp>

#include <SplayLibrary/3D/Transformable3D.hpp>

namespace spl
{
	class PerspectiveCamera : public Transformable3D
	{
		public:

			PerspectiveCamera(float aspect, float near, float far, float fov);
			PerspectiveCamera(const uvec2& resolution, float near, float far, float fov);

			void setAspect(float aspect);
			void setAspect(const uvec2& resolution);
			void setFOV(float fov);
			void setNearDistance(float near);
			void setFarDistance(float far);

			void lookAt(const vec3& position, float dutchAngle = 0.f);

			float getAspect() const;
			float getNearDistance() const;
			float getFarDistance() const;

			vec3 getUpVector() const;
			vec3 getFrontVector() const;
			vec3 getLeftVector() const;

			mat4 getViewMatrix() const;
			const mat4& getProjectionMatrix() const;

		private:

			void computeProjectionMatrix() const;

			float _aspect;
			float _near;
			float _far;
			float _fov;

			mutable bool _updateProjectionMatrix;
			mutable mat4 _projectionMatrix;
	};
}
