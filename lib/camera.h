#ifndef CAMERA_H
#define CAMERA_H
#include <GLFW/glfw3.h>
#include <iostream>
#include "neil_math.h"

class Camera{
public:
	float yaw, pitch;
	Vec3 position, target, cam_up, cam_right, world_up;
	float cameraSpeed;
	Camera();
	Camera(Vec3, Vec3);
	Mat4 getView();
	void processMouse(float, float); 
	void processKeyboard(int);

private:
	void updateCamera();
};

#endif
