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
			PerspectiveCamera(const scp::u32vec2& resolution, float near, float far, float fov);

			void setAspect(float aspect);
			void setAspect(const scp::u32vec2& resolution);
			void setFOV(float fov);
			void setNearDistance(float near);
			void setFarDistance(float far);

			void lookAt(const scp::f32vec3& position, float dutchAngle = 0.f);

			float getAspect() const;
			float getNearDistance() const;
			float getFarDistance() const;

			scp::f32vec3 getUpVector() const;
			scp::f32vec3 getFrontVector() const;
			scp::f32vec3 getLeftVector() const;

			scp::f32mat4x4 getViewMatrix() const;
			const scp::f32mat4x4& getProjectionMatrix() const;

		private:

			void _computeProjectionMatrix() const;

			float _aspect;
			float _near;
			float _far;
			float _fov;

			mutable bool _updateProjectionMatrix;
			mutable scp::f32mat4x4 _projectionMatrix;
	};
}
