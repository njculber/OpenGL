#include "program.h"

Shader::Shader(const char* vertPath, const char* fragPath){

	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertShaderFile;
	std::ifstream fragShaderFile;

	vertShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try{
		vertShaderFile.open(vertPath);
		fragShaderFile.open(fragPath);
		std::stringstream vertShaderStream, fragShaderStream;

		vertShaderStream << vertShaderFile.rdbuf();
		fragShaderStream << fragShaderFile.rdbuf();

		vertShaderFile.close();
		fragShaderFile.close();

		vertexCode = vertShaderStream.str();
		fragmentCode = fragShaderStream.str();
	}
	catch(std::ifstream:: failure e){
		std::cout << "Failure reading shader files: " << vertPath << ", " << fragPath << "\n";
	}
	const char* vertexShaderSrc = vertexCode.c_str();
	const char* fragmentShaderSrc = fragmentCode.c_str();

	/********************************* COMPILE **************************************/
	int success;
    char infoLog[512];

	// link vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Vertex loading ERROR " << infoLog << std::endl;
    }


    // link fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Fragment loading ERROR " << infoLog << std::endl;
    }


    /********************************* LINKING **************************************/

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "Error linking shader" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use(){
	glUseProgram(ID);
}

void Shader::setFloat(const char * uni, float val){
	int loc = glGetUniformLocation(ID, uni);
    if(loc == -1) std::cout << "ERROR with uniform location " << uni << "\n";
	glUniform1f(loc, val);
}

void Shader::setInt(const char *uni, int val){
    int loc = glGetUniformLocation(ID, uni);
    if(loc == -1) std::cout << "ERROR with uniform location " << uni << "\n";
    glUniform1i(loc, val);
}

void Shader::setVec3f(const char *uni, float v1, float v2, float v3){
	int loc = glGetUniformLocation(ID, uni);
    if(loc == -1) std::cout << "ERROR with uniform location " << uni << "\n";
	glUniform3f(loc, v1, v2, v3);
}

void Shader::setVec3f(const char *uni, glm::vec3 vec){
    int loc = glGetUniformLocation(ID, uni);
    if(loc == -1) std::cout << "ERROR with uniform location " << uni << "\n";
    glUniform3f(loc, vec.x, vec.y, vec.z);
}

void Shader::setVec3f(const char *uni, Vec3 vec){
    int loc = glGetUniformLocation(ID, uni);
    if(loc == -1) std::cout << "ERROR with uniform location " << uni << "\n";
    glUniform3f(loc, vec.x, vec.y, vec.z);
}

void Shader::setMat4(const char *uni, glm::mat4 mat){
    unsigned int matLoc = glGetUniformLocation(ID, uni);
    if(matLoc < 0) std::cout << "ERROR with uniform location " << uni << "\n";
    glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMat4(const char *uni, Mat4 mat){
    unsigned int matLoc = glGetUniformLocation(ID, uni);
    if(matLoc < 0) std::cout << "ERROR with uniform location " << uni << "\n";
    glUniformMatrix4fv(matLoc, 1, GL_FALSE, mat.mat);
}

GLint Shader::getAttribLoc(const char *att){
    GLint loc = glGetAttribLocation(ID, att);
    if(loc == -1) std::cout << "ERROR with attribute location " << att << "\n";
    return glGetAttribLocation(ID, att);
}












