#ifndef VECTOR_H
#define VECTOR_H
#ifndef M_PI
#define M_PI 3.1415926535
#endif
#include <cmath>

class Vec3{
public:
	float x, y, z;
	Vec3();
	Vec3(float, float, float);
	float magnitude();
	void normalize();
	Vec3 cross(Vec3);
	void show();
	Vec3 operator - (Vec3);
	Vec3 operator + (Vec3);
	Vec3 operator -= (Vec3);
	Vec3 operator += (Vec3);
	Vec3 operator * (float);
};

class Mat4{
public:
	float mat[16];
	Mat4();
	Mat4(float);
	void toIdentity();
	void show();
	void showInverted();
	Mat4 operator * (Mat4);
	static Mat4 rotate(Mat4, float, Vec3);
	static Mat4 translate(Mat4, Vec3);
	static Mat4 scale(Mat4, Vec3);
	static Mat4 lookAt(Vec3, Vec3, Vec3);
	// static Mat4 perspective();
};



#endif
