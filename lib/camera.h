#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "neil_math.h"

class Camera{
public:
	float yaw, pitch;
	glm::vec3 cameraPos, cameraFront, cameraUp, cameraRight, worldUp;
	Vec3 position, target, cam_up, cam_right, world_up; //!!!!!!!!!!!!!!!! update
	float cameraSpeed;
	Camera();
	Camera(glm::vec3, glm::vec3);
	Camera(Vec3, Vec3); // !!!!!!!!!!!!!!!!!! update
	glm::mat4 getView();
	Mat4 getView_();
	void processMouse(float, float);
	void processKeyboard(int);

private:
	void updateCamera();
	void updateCamera_(); // !!!!!!!!!!!!!!! update
};

#endif
