/**
	Voxel Welt - COMP 371 Fall 2015 Project
	main.cpp
	Purpose: Entry point of application.

	@author Patrick Soueida
	@author Maxwell Mowbray
	@version M0.0
*/

#include "stdafx.h"

#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library

#include "glm.hpp"
#include "gtc/type_ptr.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <string>
#include <fstream>

using namespace std;

GLFWwindow* window = 0x00;

GLuint shader_programme = 0;

GLuint vao = 0, vertices_vbo = 0;

GLuint model_matrix_id = 0; 
GLuint view_matrix_id = 0;
GLuint proj_matrix_id = 0;

glm::mat4 model_matrix;
glm::mat4 proj_matrix; 
glm::mat4 view_matrix;

/**
	Loads GLFW and GLEW.

	@return a boolean representing whether or not there was an erorr during initialization.
*/

bool initialize() {
	// Initialize GL context and O/S window using the GLFW helper library
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return false;
	}

	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	window = glfwCreateWindow(1280, 720, "Voxel Welt", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	/// Initialize GLEW extension handler
	glewExperimental = GL_TRUE;	///Needed to get the latest version of OpenGL
	glewInit();

	const GLubyte* renderer = glGetString(GL_RENDERER); /// Get renderer string
	const GLubyte* version = glGetString(GL_VERSION); /// Version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	/// Enable the depth test i.e. draw a pixel if it's closer to the viewer
	glEnable(GL_DEPTH_TEST); /// Enable depth-testing
	glDepthFunc(GL_LESS);	/// The type of testing i.e. a smaller value as "closer"

	return true;
}

/**
	Frees up memory before the program terminates.

	@return void.
*/

void cleanUp() {
	
	//Release VAO/VBO memory
	glDeleteProgram(shader_programme);
	glDeleteBuffers(1, &vertices_vbo);
	glDeleteVertexArrays(1, &vao);

	// Close GL context and any other GLFW resources
	glfwTerminate();
}

/**
	Loads the vertex and fragments shaders from text files and creates an OpenGL Programme.

	@param the path of the vertex shader.
	@param the path of the fragment shader.
	@return the OpenGL Programme ID to be used.
*/

GLuint loadShaders(std::string vertex_shader_path, std::string fragment_shader_path) {
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_shader_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_shader_path.c_str());
		getchar();
		exit(-1);
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_shader_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", fragment_shader_path.c_str());
		getchar();
		exit(-1);
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_shader_path.c_str());
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_shader_path.c_str());
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint programme_id = glCreateProgram();
	glAttachShader(programme_id, VertexShaderID);
	glAttachShader(programme_id, FragmentShaderID);
	
	glBindAttribLocation(programme_id, 0, "in_Position");
	glBindFragDataLocation(programme_id, 0, "out_Color");

	glLinkProgram(programme_id);

	// Check the program
	glGetProgramiv(programme_id, GL_LINK_STATUS, &Result);
	glGetProgramiv(programme_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(programme_id, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(programme_id, VertexShaderID);
	glDetachShader(programme_id, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	//The three variables below hold the id of each of the variables in the shader
	model_matrix_id = glGetUniformLocation(programme_id, "model_matrix");
	view_matrix_id = glGetUniformLocation(programme_id, "view_matrix");
	proj_matrix_id = glGetUniformLocation(programme_id, "proj_matrix");
	
	return programme_id;
}

int main() {

	assert(sizeof(glm::vec3) == sizeof(float) * 3 && sizeof(glm::uvec3) == sizeof(unsigned int) * 3);

	initialize();

	glGenVertexArrays(1, &vao);	// Create Vertex Array Object
	glBindVertexArray(vao); //and select it

	std::vector<GLfloat> vertices;

	float points[9] = {
		0.5, -0.5, 0,
		0.5, 0.5, 0,
		-0.5, 0.5, 0
	};

	for (int i = 0; i < 9; i++){
		vertices.push_back(points[i]);
	}

	glGenBuffers(1, &vertices_vbo); //generate 1 VBO for the vertices
	glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW); //copy vertex data into the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	shader_programme = loadShaders("vertex.shader", "fragment.shader");

	glUseProgram(shader_programme);

	while (!glfwWindowShouldClose(window)) {
		
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Pass the values of the three matrices to the shaders
		glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(proj_matrix_id, 1, GL_FALSE, glm::value_ptr(proj_matrix));
		
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
	}

	cleanUp();
	return 0;
}
