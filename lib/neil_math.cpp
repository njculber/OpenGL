#include "neil_math.h"
#include <iostream>
#include <iomanip>


/************************* VECTOR **************************/
Vec3::Vec3(){
	x = 0.0f; y = 0.0f; z = 0.0f;
}

Vec3::Vec3(float x_in, float y_in, float z_in){
	x = x_in;
	y = y_in;
	z = z_in;
}

float Vec3::magnitude(){
	return sqrt( (x*x) + (y*y) + (z*z) );
}

void Vec3::normalize(){
	x = x / magnitude();
	y = y / magnitude();
	z = z / magnitude();
}

Vec3 Vec3::cross(Vec3 vec){
	return Vec3( (y * vec.z) - (z * vec.y), 
			     (z * vec.x) - (x * vec.z), 
				 (x * vec.y) - (y * vec.x) 
				);
}

void Vec3::show(){
	std::cout << "< " << x << ", " << y << ", " << z << " >\n";
}

Vec3 Vec3::operator - (Vec3 vec){
	return Vec3(x-vec.x, y-vec.y, z-vec.z);
}
Vec3 Vec3::operator + (Vec3 vec){
	return Vec3(x+vec.x, y+vec.y, z+vec.z);
}

Vec3 Vec3::operator -= (Vec3 vec){
	return Vec3(x -= vec.x, y -= vec.y, z -= vec.z);
}
Vec3 Vec3::operator += (Vec3 vec){
	return Vec3(x += vec.x, y += vec.y, z += vec.z);
}
Vec3 Vec3::operator * (float in){
	return Vec3(x * in, y * in, z * in);
}


/************************* MATRIX **************************/
void Mat4::show(){
	int width = 12;
	for(int i = 0; i < 4; i += 1){
		std::cout << std::left;
		std::cout << "[ " << std::setw(width) << mat[i] << " " << std::setw(width) << 
			mat[i+4] << " " <<  std::setw(width) << mat[i+8] << " " << mat[i+12] << " ]\n"; 
	}
	std::cout << "\n";
}

void Mat4::showInverted(){
	int width = 12;
	int index = 0;
	for(int i = 0; i < 4; i += 1){
		index = i*4;
		std::cout << std::left;
		std::cout << "[ " << std::setw(width) << mat[index] << " " << std::setw(width) << 
			mat[index+1] << " " <<  std::setw(width) << mat[index+2] << " " << mat[index+3] << " ]\n"; 
	}
	std::cout << "\n";
}

Mat4::Mat4(){
	for(int i = 0; i < 16; i += 1){
		mat[i] = 0;
	}
}

Mat4::Mat4(float in){
	for(int i = 0; i < 16; i += 1){
		if(i%5 == 0) mat[i] = in;
		else mat[i] = 0;
	}
}

void Mat4::toIdentity(){
	for(int i = 0; i < 16; i += 1){
		if(i%5 == 0) mat[i] = 1.0f;
		else mat[i] = 0;
	}
}

Mat4 Mat4::operator * (Mat4 mat_in){
	Mat4 m;
	int index = 0;
	int jdex = 0;
	for(int i = 0; i < 4; i += 1){
		for(int j = 0; j < 4; j += 1){
			index = (i*4) + j;
			jdex = (j*4);
			m.mat[jdex + i] = (mat[i]*mat_in.mat[jdex]) + (mat[i+4]*mat_in.mat[jdex+1]) +
						(mat[i+8]*mat_in.mat[jdex+2]) + (mat[i+12]*mat_in.mat[jdex+3]);
		}
	}
	return m;
}

float radians(float angle){
	return (angle * M_PI) / 180.0f;
}

Mat4 rotate(Mat4 m, float angle, Vec3 vec){
	Mat4 m1(1.0f);
	float n = 1-cos(angle);
	float x = vec.x / vec.magnitude();
	float y = vec.y / vec.magnitude();
	float z = vec.z / vec.magnitude();

	m1.mat[0] =  cos(angle) + (x*x*n);
	m1.mat[1] =  (y*x*n) + (z * sin(angle));
	m1.mat[2] =  (z*x*n) - (y * sin(angle));

	m1.mat[4] =  (x*y*n) - (z * sin(angle));
	m1.mat[5] =  cos(angle) + (y*y*n);
	m1.mat[6] =  (z*y*n) + (x * sin(angle));

	m1.mat[8] =  (x*z*n) + (y * sin(angle));
	m1.mat[9] =  (y*z*n) - (x * sin(angle));
	m1.mat[10] = cos(angle) + (z*z*n);

	return m1 * m;
}

Mat4 translate(Mat4 m, Vec3 vec){	
	Mat4 m1(1.0f);
	m1.mat[12] += vec.x;
	m1.mat[13] += vec.y;
	m1.mat[14] += vec.z;
	return m1 * m;
}

Mat4 scale(Mat4 m, Vec3 vec){
	Mat4 m1(1.0f);
	m1.mat[0] *= vec.x;
	m1.mat[5] *= vec.y;
	m1.mat[10] *= vec.z;
	return m1 * m;
}

Mat4 lookAt(Vec3 position, Vec3 target, Vec3 up){
	// calculate direction, right, and up vectors
	Vec3 direction = position - target;
	Vec3 right = up.cross(direction);
	Vec3 new_up = direction.cross(right);
	right.normalize();
	direction.normalize();
	new_up.normalize();

	// create rotation matrix
	Mat4 rm;
	rm.toIdentity();

	rm.mat[0] = right.x;
	rm.mat[4] = right.y;
	rm.mat[8] = right.z;
	rm.mat[1] = new_up.x;
	rm.mat[5] = new_up.y;
	rm.mat[9] = new_up.z;
	rm.mat[2] = direction.x;
	rm.mat[6] = direction.y;
	rm.mat[10] = direction.z;

	// create translation matrix
	Mat4 tm;
	tm.toIdentity();

	tm.mat[12] = -position.x;
	tm.mat[13] = -position.y;
	tm.mat[14] = -position.z;

	// return rotation * translation matrix
	return rm * tm;
}

Mat4 perspective(float fov, float aspectRatio, float near, float far){ 
	// calculate desired boundaries
    float scale = tan(fov * 0.5 * M_PI / 180) * near; 
    float right = aspectRatio * scale; 
    float left = -right; 
    float top = scale;
    float bottom = -top; 

    // set up perspective matrix
	Mat4 m(0.0f);
    m.mat[0] = near / ((right-left)/2);
	m.mat[5] = near / ((top-bottom)/2);
	m.mat[10] = -(far+near) / (far-near);
	m.mat[11] = -1.0f;
	m.mat[14] = -(2 * (far*near)) / (far-near);
	m.mat[15] = 0.0f;
	
	return m;
}





































