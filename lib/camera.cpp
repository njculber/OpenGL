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

glm::mat4 Camera::getView(){
	return glm::lookAt(cameraPos, // position
                        cameraPos + cameraFront, // target
                        cameraUp); // up vector
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
