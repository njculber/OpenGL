#include "camera.h"


Camera::Camera(){
	cameraSpeed = 0.05;
	cameraPos = glm::vec3(0.0, 0.0, 3.0);
	cameraFront = glm::vec3(0.0, 0.0, -1.0);
	cameraUp = glm::vec3(0.0, 1.0, 0.0);
	worldUp = glm::vec3(0.0, 1.0, 0.0);
	yaw = -90.0f;
	pitch = 0.0f;
	updateCamera();
}

Camera::Camera(glm::vec3 pos, glm::vec3 target){
	cameraSpeed = 0.05;
	cameraPos = pos;
	cameraFront = target;
	cameraUp = glm::vec3(0.0, 0.0, 0.0);
	worldUp = glm::vec3(0.0, 1.0, 0.0);
	yaw = -90.0f;
	pitch = 0.0f;
	updateCamera();
}

Camera::Camera(Vec3 pos, Vec3 target_in){ // !!!!!!!!!!!!!!!!! update
	cameraSpeed = 0.05;
	position = pos;
	target = target_in;
	cam_up = Vec3(0.0, 0.0, 0.0);
	world_up = Vec3(0.0, 1.0, 0.0);
	yaw = -90.0f;
	pitch = 0.0f;
	updateCamera();
}

glm::mat4 Camera::getView(){
	return glm::lookAt(cameraPos, // position
                        cameraPos + cameraFront, // target
                        cameraUp); // up vector
}

Mat4 Camera::getView_(){ // !!!!!!!!!!!!!!!!!! update
    Vec3 forward = position - target;
    forward.normalize();                 // make unit length

    // // compute the left vector
    Vec3 right = forward.cross(cam_up); // cross product
    right.normalize();

    // // recompute the orthonormal up vector
    Vec3 up = forward.cross(right);    // cross product

    // // init 4x4 matrix
    Mat4 matrix(1.0f);
    matrix.mat[0] = right.x;
    matrix.mat[4] = right.y;
    matrix.mat[8] = right.z;

    matrix.mat[1] = up.x;
    matrix.mat[5] = up.y;
    matrix.mat[9] = up.z;

    matrix.mat[2] = forward.x;
    matrix.mat[6] = forward.y;
    matrix.mat[10] = forward.z;

    matrix.mat[12] = right.x * position.x - right.y * position.y - right.z * position.z;
    matrix.mat[13] = up.x * position.x - up.y * position.y - up.z * position.z;
    matrix.mat[14] = forward.x * position.x - forward.y * position.y - forward.z * position.z;

    return matrix;
}

void Camera::processMouse(float x_off, float y_off){
	float sensitivity = 0.1f;
    x_off *= sensitivity;
    y_off *= sensitivity;
    yaw += x_off;
    pitch += y_off;

    updateCamera();
    // updateCamera_();
}

void Camera::processKeyboard(int val){
	if(val == 1) cameraPos -= cameraFront * cameraSpeed;
	if(val == 2) cameraPos += cameraFront * cameraSpeed;
	if(val == 3) cameraPos += cameraRight * cameraSpeed;
	if(val == 4) cameraPos -= cameraRight * cameraSpeed;
}

void Camera::updateCamera(){
	glm::vec3 front;

    front.x = ( cos(glm::radians(yaw)) * cos(glm::radians(pitch)) );
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

void Camera::updateCamera_(){ // !!!!!!!!!!!!!!!! update
	Vec3 front;

    front.x = ( cos(glm::radians(yaw)) * cos(glm::radians(pitch)) );
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    target = front;

    cam_right = target.cross(world_up);
    cam_right.normalize();
    cam_up = cam_right.cross(target);
    cam_up.normalize();
}
