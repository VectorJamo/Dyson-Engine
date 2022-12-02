#include "orthographic_camera.h"
#include "maths/constants.h"

#include "util/timer.h"
#include "util/input.h"
#include "util/error_handling.h"

namespace ds {
	namespace util {
		maths::vec2 OrthographicCamera::pCameraPosition;
		ProjectionBounds OrthographicCamera::pCameraBounds;
		float OrthographicCamera::pCameraSpeed = 400.0f;
		float OrthographicCamera::pCameraRotationSpeed = 100.0f;
		float OrthographicCamera::pZoomFactor = 1.0f;
		float OrthographicCamera::pZoomIncrement = 100.0f;
		float OrthographicCamera::pRotationAngle = 0.0f;

		maths::mat4 OrthographicCamera::pProjectionMatrix;
		maths::mat4 OrthographicCamera::pCameraTranslation;
		maths::mat4 OrthographicCamera::pCameraRotation;
		bool OrthographicCamera::IsInitialized = false;

		void OrthographicCamera::Init(float left, float right, float top, float bottom, float zNear, float zFar)
		{
			IsInitialized = true;

			pProjectionMatrix = maths::orthographic(left, right, top, bottom, zNear, zFar);
			pCameraBounds = { left, right, top, bottom, zNear, zFar };

			CreateViewMatrix();
			
#if _DEBUG
			std::cout << " -> Orthographic Camera Initialized!" << std::endl;
#endif
		}

		void OrthographicCamera::SetPosition(const maths::vec2& pos)
		{
			pCameraPosition = pos;

			CreateViewMatrix();
		}

		void OrthographicCamera::SetZoomSpeed(float zoomIncrement)
		{
			if (zoomIncrement > 500.0f || zoomIncrement < 10.0f)
			{
				THROW_ERROR("Use a value between 10 and 500");
				return;
			}
			pZoomIncrement = zoomIncrement;
		}
		void OrthographicCamera::SetCameraSpeed(float cameraSpeed)
		{
			pCameraSpeed = cameraSpeed;
		}
		void OrthographicCamera::SetRotationSpeed(float rotationSpeed)
		{
			pCameraRotationSpeed = rotationSpeed;
		}

		void OrthographicCamera::ZoomIn()
		{
			pZoomFactor -= (pZoomIncrement * Timer::GetDeltaTime());
			if (pZoomFactor <= 0.05f)
				pZoomFactor = 0.05f;
			else
				pProjectionMatrix = maths::orthographic(pCameraBounds.left * pZoomFactor, pCameraBounds.right * pZoomFactor, pCameraBounds.top * pZoomFactor, pCameraBounds.bottom * pZoomFactor, pCameraBounds.zNear, pCameraBounds.zFar);
		}

		void OrthographicCamera::ZoomOut()
		{
			pZoomFactor += (pZoomIncrement * Timer::GetDeltaTime());
			if (pZoomFactor >= 5.0f)
				pZoomFactor = 5.0f;
			else
				pProjectionMatrix = maths::orthographic(pCameraBounds.left * pZoomFactor, pCameraBounds.right * pZoomFactor, pCameraBounds.top * pZoomFactor, pCameraBounds.bottom * pZoomFactor, pCameraBounds.zNear, pCameraBounds.zFar);
		}
		void OrthographicCamera::Rotate(float angle)
		{
			pRotationAngle = angle;

			CreateViewMatrix();
		}

		void OrthographicCamera::CreateViewMatrix()
		{
			pCameraTranslation = maths::translate(maths::vec3(-pCameraPosition.x, -pCameraPosition.y, 0.0f));
			pCameraRotation = maths::rotate(TO_RADIANS(pRotationAngle), maths::vec3(0.0f, 0.0f, 1.0f));
		}

		void OrthographicCamera::UpdateControls()
		{
			// Camera controls
			if (Input::IsKeyHold(DS_KEY_A))
				pCameraPosition.x -= pCameraSpeed * Timer::GetDeltaTime();
			if (Input::IsKeyHold(DS_KEY_D))
				pCameraPosition.x += pCameraSpeed * Timer::GetDeltaTime();
			if (Input::IsKeyHold(DS_KEY_W))
				pCameraPosition.y += pCameraSpeed * Timer::GetDeltaTime();
			if (Input::IsKeyHold(DS_KEY_S))
				pCameraPosition.y -= pCameraSpeed * Timer::GetDeltaTime();

			if (Input::IsKeyHold(DS_KEY_LEFT))
			{
				pRotationAngle -= (pCameraRotationSpeed * Timer::GetDeltaTime());
				Rotate(pRotationAngle);
			}
			if (Input::IsKeyHold(DS_KEY_RIGHT))
			{
				pRotationAngle += (pCameraRotationSpeed * Timer::GetDeltaTime());
				Rotate(pRotationAngle);
			}
			if (Input::IsMouseScrollUp())
				ZoomIn();
			if (Input::IsMouseScrollDown())
				ZoomOut();

			// Reset's the camera's transform
			if (Input::IsKeyHold(DS_KEY_R))
			{
				pCameraPosition = { 0.0f, 0.0f };
				pRotationAngle = 0.0f;
				pZoomFactor = 1.0f;

				pProjectionMatrix = maths::orthographic(pCameraBounds.left * pZoomFactor, pCameraBounds.right * pZoomFactor, pCameraBounds.top * pZoomFactor, pCameraBounds.bottom * pZoomFactor, pCameraBounds.zNear, pCameraBounds.zFar);
			}
			CreateViewMatrix();
		}

		ProjectionBounds::ProjectionBounds()
			:left(-1), right(1), top(1), bottom(-1), zNear(1.0f), zFar(-1.0f)
		{
		}

		ProjectionBounds::ProjectionBounds(float left, float right, float top, float bottom, float zNear, float zFar)
			: left(left), right(right), top(top), bottom(bottom), zNear(zNear), zFar(zFar)
		{
		}
	}
}

