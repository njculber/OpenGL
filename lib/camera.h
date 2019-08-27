#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Camera{
public:
	float yaw, pitch;
	glm::vec3 cameraPos, cameraFront, cameraUp, cameraRight, worldUp;
	float cameraSpeed;
	Camera();
	Camera(glm::vec3, glm::vec3);
	glm::mat4 getView();
	void processMouse(float, float);
	void processKeyboard(int);

private:
	void updateCamera();
};
