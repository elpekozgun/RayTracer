class Vector3
{
public:
	float x;
	float y;
	float z;


	Vector3(float x, float y, float z);
	Vector3();

	float DotProduct(Vector3 other);
	float DotProductNormalized(Vector3 other);
	Vector3 CrossProduct(Vector3 other);
	float DistanceToOther(Vector3 other);

	~Vector3();
};
