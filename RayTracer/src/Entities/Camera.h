#ifndef CAMERA_H
#define CAMERA_H

#include "../Core/Vector3.h"
#include "..//Entities/IEntity.h"

struct Vector2
{
	float x;
	float y;
};

struct Vector4
{
	float l;
	float r;
	float b;
	float t;
};


class Camera : public IEntity
{
public:

	Vector3 Position;
	Vector3 Gaze;
	Vector3 Up;
	Vector4 NearPlane;
	float NearDistance;
	Vector2 ScreenResolution;

	Vector3 GetScreenPixel(float i, float j);


	Camera();
	Camera(Vector3 position, Vector3 gaze, Vector3 up, Vector4 nearPlane, float nearDistance, Vector2 screenResolution);
	~Camera();

private:


	// Inherited via IEntity
	virtual eEntityType GetType() override;

};

#endif 
