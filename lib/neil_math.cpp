#include "neil_math.h"
#include <iostream>
#include <cmath>

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

Vec3 Vec3::operator - (Vec3 vec){
	return Vec3(x-vec.x, y-vec.y, z-vec.z);
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

void Mat4::show(){
	for(int i = 0; i < 16; i += 4){
		std::cout << "[ " << mat[i] << " " << mat[i+1] << " " << mat[i+2] << " " << mat[i+3] << " ]\n"; 
	}
}
