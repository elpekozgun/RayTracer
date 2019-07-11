#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "ValueType.h"

struct Vector2
{
	float x;
	float y;
};

struct Vector4
{
	float x;
	float y;
	float z;
	float w;
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



	Camera();
	~Camera();

private:


	// Inherited via IEntity
	virtual eEntityType GetType() override;

};

#endif 
