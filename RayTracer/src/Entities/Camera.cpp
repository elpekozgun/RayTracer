#include "Camera.h"

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
	"Camera Destroyed";
}

eEntityType Camera::GetType()
{
	return eEntityType::camera;
}
