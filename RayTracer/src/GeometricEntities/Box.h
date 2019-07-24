#ifndef BOX_H
#define BOX_H

#include "IGeometricEntity.h"

class Box : public IGeometricEntity
{
public:

	Vector3 bounds[2];

	Box();
	Box(const Vector3 vMin, const Vector3 vMax);
	~Box();


	virtual std::pair<float, IGeometricEntity*> Intersect(Ray ray) override;
	virtual Vector3 GetNormal(Vector3 point) override;
	virtual int ID() override;
	virtual int MaterialID() override;

private:
	int MaterialId;
	int Id;

	// Inherited via IGeometricEntity


};



#endif 
