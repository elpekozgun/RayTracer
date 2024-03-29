#ifndef BOX_H
#define BOX_H

#include "IGeometricEntity.h"
#include "Sphere.h"

class Box : public IGeometricEntity
{
public:

	Vector3 bounds[2];

	Box();
	Box(const Vector3 vMin, const Vector3 vMax);
	~Box();


	bool isPointInside(Vector3 point);

	virtual IGeometricEntity* Intersect(Ray ray, float& t) override;
	virtual Vector3 GetNormal(Vector3 point) override;
	virtual int ID() override;
	virtual int MaterialID() override;

private:
	int MaterialId;
	int Id;

	// Inherited via IGeometricEntity


};



#endif 
