#pragma once

#include "../maths/vec/vec2.h"
#include "../maths/vec/vec3.h"
#include "../maths/mat/mat4.h"

namespace ds {
	namespace util {
		struct DS ProjectionBounds
		{
			float left, right, top, bottom, zNear, zFar;
			ProjectionBounds();
			ProjectionBounds(float left, float right, float top, float bottom, float zNear, float zFar);
		};
		class DS OrthographicCamera
		{
		private:
			// Camera's transform
			static maths::vec2 pCameraPosition;
			static ProjectionBounds pCameraBounds;
			static float pCameraSpeed;
			static float pCameraRotationSpeed;
			static float pZoomFactor;
			static float pZoomIncrement;
			static float pRotationAngle;

			// Camera's transform matrices
			static maths::mat4 pProjectionMatrix;
			static maths::mat4 pCameraTranslation;
			static maths::mat4 pCameraRotation;

			static bool IsInitialized;

		public:
			static bool DisableRotation;
			static bool DisableZoom;
			static bool DisableTranslation;

		private:
			static void CreateViewMatrix();

		public:

			OrthographicCamera() = delete;

			// Setters
			static void Init(float left, float right, float top, float bottom, float zNear, float zFar);
			static void SetPosition(const maths::vec2& pos);
			static void Rotate(float angle);

			static void SetCameraSpeed(float cameraSpeed);
			static void SetRotationSpeed(float rotationSpeed);
			static void SetZoomSpeed(float zoomIncrement);

			static void ZoomIn();
			static void ZoomOut();

			static void UpdateControls();

			// Getters
			inline static maths::vec2 GetCameraPosition() { return pCameraPosition; }
			inline static maths::mat4 GetProjectionMatrix() { return pProjectionMatrix; }
			inline static maths::mat4 GetCameraTranslationMatrix() { return pCameraTranslation; }
			inline static maths::mat4 GetCameraRotationMatrix() { return pCameraRotation; }
			inline static bool IsCameraInitialized() { return IsInitialized; }
		};
	}
}