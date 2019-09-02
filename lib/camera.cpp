#include "camera.h"

Camera::Camera(){
    cameraSpeed = 0.05;
    position = Vec3(0.0, 0.0, 3.0);
    target = Vec3(0.0, 0.0, -1.0);
    cam_up = Vec3(0.0, 1.0, 0.0);
    world_up = Vec3(0.0, 1.0, 0.0);
    yaw = -90.0f;
    pitch = 0.0f;
    updateCamera();
}

Camera::Camera(Vec3 pos, Vec3 target_in){ 
	cameraSpeed = 0.05;
	position = pos;
	target = target_in;
	cam_up = Vec3(0.0, 1.0, 0.0);
	world_up = Vec3(0.0, 1.0, 0.0);
	yaw = -90.0f;
	pitch = 0.0f;
	updateCamera();
}

Mat4 Camera::getView(){
    return Mat4::lookAt(position, position + target, cam_up);
}

void Camera::processMouse(float x_off, float y_off){
	float sensitivity = 0.1f;
    x_off *= sensitivity;
    y_off *= sensitivity;
    yaw += x_off;
    pitch += y_off;

    updateCamera();
}

void Camera::processKeyboard(int val){
    if(val == 1) position -= target * cameraSpeed;
    if(val == 2) position += target * cameraSpeed;
    if(val == 3) position += cam_right * cameraSpeed;
    if(val == 4) position -= cam_right * cameraSpeed;
}

void Camera::updateCamera(){
	Vec3 front;
    float yawRad = (yaw * M_PI) / 180.0f;
    float pitchRad = (pitch * M_PI) / 180.0f;

    front.x = cos(yawRad) * cos(pitchRad);
    front.y = sin(pitchRad);
    front.z = sin(yawRad) * cos(pitchRad);
    front.normalize();
    target = front;

    cam_right = target.cross(world_up);
    cam_right.normalize();

    cam_up = cam_right.cross(target);
    cam_up.normalize();
}















