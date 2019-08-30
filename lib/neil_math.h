#ifndef VECTOR_H
#define VECTOR_H

class Vec3{
public:
	float x, y, z;
	Vec3();
	Vec3(float, float, float);
	float magnitude();
	void normalize();
	Vec3 cross(Vec3);
	Vec3 operator - (Vec3);
};

class Mat4{
public:
	float mat[16];
	Mat4();
	Mat4(float);
	void show();
};

#endif
