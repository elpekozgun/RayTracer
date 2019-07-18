#include "Camera.h"

Vector3 Camera::GetScreenPixel(int i, int j)
{
	auto sU = (NearPlane.r - NearPlane.l) * (i + 0.5f) / ScreenResolution.x;
	auto sV = (NearPlane.t - NearPlane.b) * (j + 0.5f) / ScreenResolution.y;

	return Vector3(NearPlane.l + sU, NearPlane.t - sV, -NearDistance);
}

Camera::Camera()
{
	this->Position = Vector3();
	this->Gaze = Vector3();
	this->Up = Vector3();
	this->NearPlane = Vector4();
	this->NearDistance = 0.0f;
	this->ScreenResolution = Vector2();
}

Camera::Camera(Vector3 position, Vector3 gaze, Vector3 up, Vector4 nearPlane, float nearDistance, Vector2 screenResolution)
{
	this->Position = position;
	this->Gaze = gaze;
	this->Up = up;
	this->NearPlane = nearPlane;
	this->NearDistance = nearDistance;
	this->ScreenResolution = screenResolution;
}

Camera::~Camera()
{
	std::cout << "Camera Destroyed" << std::endl;
}

eEntityType Camera::GetType()
{
	return eEntityType::camera;
}
