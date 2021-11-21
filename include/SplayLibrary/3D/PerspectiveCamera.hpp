#pragma once

#include <SplayLibrary/3D/types.hpp>

#include <SplayLibrary/Core/Glsl.hpp>
#include <SplayLibrary/3D/Transformable3D.hpp>

namespace spl
{
	class PerspectiveCamera : public Transformable3D
	{
		public:

			PerspectiveCamera(float aspect, float near, float far, float fov);
			PerspectiveCamera(const uvec2& resolution, float near, float far, float fov);

			// TODO: Up, Front, Left (Transformable or just camera ?)
			// TODO: LookAt(vec3)

			void setAspect(float aspect);
			void setAspect(const uvec2& resolution);
			void setFOV(float fov);
			void setNearDistance(float near);
			void setFarDistance(float far);

			float getAspect() const;
			const vec2& getFOV() const;
			float getNearDistance() const;
			float getFarDistance() const;
			const mat4& getViewMatrix() const;
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
