/**
	Metropol - COMP 371 Fall 2015 Project
	main.cpp
	Purpose: Entry point of application.

	@author Patrick Soueida
	@author Maxwell Mowbray
	@version M0.1
*/

#include "stdafx.h"

#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library

#include "glm.hpp"
#include "transform.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

#define M_PI 3.14159265358979323846264338327950288

GLFWwindow* window = 0x00;

GLuint shader_programme = 0;

GLuint vao = 0, terrain_vertices_vbo = 0, terrain_indices_vbo = 0;

GLuint model_matrix_id = 0; 
GLuint view_matrix_id = 0;
GLuint proj_matrix_id = 0;

glm::mat4 model_matrix;
glm::mat4 proj_matrix; 
glm::mat4 view_matrix;

//camera position vector
glm::vec3 camera_position;
float old_mouse_y_pos;

/**
	Reacts to mouse scrollwheel input.

	@return void.
*/

void cursorMoved(GLFWwindow* window, double xpos, double ypos) {

	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) && (ypos != old_mouse_y_pos)) { //dragging up or down

		if (ypos > old_mouse_y_pos) {
			camera_position.z += 1.0f;
		}
		else {
			camera_position.z -= 1.0f;
		}

		camera_position.z = max(camera_position.z, 1.0f); //clamp the camera position
		old_mouse_y_pos = ypos;
	}

}

/**
	Updates the vieport and perspective matrix when the window is resized.

	@return void.
*/

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height); //update the viewport on window resize

	// Update the Projection matrix after a window resize event
	proj_matrix = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
}

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
	window = glfwCreateWindow(1280, 720, "Metropol", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return false;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, cursorMoved);

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

	//setup other variables
	camera_position = glm::vec3(0.0f, 10.0f, 1.0f);

	proj_matrix = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);

	return true;
}

/**
	Frees up memory before the program terminates.

	@return void.
*/

void cleanUp() {
	
	//Release VAO/VBO memory
	glDeleteProgram(shader_programme);
	glDeleteBuffers(1, &terrain_vertices_vbo);
	glDeleteBuffers(1, &terrain_indices_vbo);
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

	std::vector<GLuint> terrain_indices;
	std::vector<GLfloat> terrain_points;

	int terrain_mesh_width = 40, terrain_mesh_height = 40; //terrain mesh dimensions

	for (int y = 0; y < terrain_mesh_height; y++) {
		for (int x = 0; x < terrain_mesh_width; x++) {
			
			terrain_points.push_back(x);
			terrain_points.push_back(y);
			terrain_points.push_back(0.0f);

			//index ordering algorithm
			if (x < terrain_mesh_width - 1 && y < terrain_mesh_width - 1)
			{
				//top triangle
				terrain_indices.push_back(x + y * terrain_mesh_width);
				terrain_indices.push_back(x + 1 + y * terrain_mesh_width);
				terrain_indices.push_back(x + (y + 1) * terrain_mesh_width);

				//botom triangle
				terrain_indices.push_back(x + 1 + y * terrain_mesh_width);
				terrain_indices.push_back(x + 1 + (y + 1) * terrain_mesh_width);
				terrain_indices.push_back(x + (y + 1) * terrain_mesh_width);

			}
		}
	}

	glGenBuffers(1, &terrain_vertices_vbo); //generate 1 VBO for the terrain vertices
	glBindBuffer(GL_ARRAY_BUFFER, terrain_vertices_vbo);
	glBufferData(GL_ARRAY_BUFFER, terrain_points.size() * sizeof(GLfloat), &terrain_points.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &terrain_indices_vbo); //generate 1 VBO for the terrain vertex indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrain_indices_vbo); //select the indices VBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, terrain_indices.size() * sizeof(unsigned int), &terrain_indices.front(), GL_STATIC_DRAW); //copy indices data into the VBO

	shader_programme = loadShaders("vertex.shader", "fragment.shader");

	GLint posAttrib = glGetAttribLocation(shader_programme, "in_Position"); //enable the position input to the shaders
	glEnableVertexAttribArray(posAttrib);

	glUseProgram(shader_programme);

	while (!glfwWindowShouldClose(window)) {
		
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//update the camera matrix
		view_matrix = glm::lookAt(
			glm::vec3(camera_position),
			glm::vec3(0), //looking at origin for now
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

		glm::mat4 terrain_mesh_translate = glm::translate(glm::vec3(-(float)terrain_mesh_width / 2, -(float)terrain_mesh_height/ 2, 0)); //center the terrain mesh
		glm::mat4 terrain_mesh_rotate = glm::rotate(glm::mat4(), (float)M_PI / 2, glm::vec3(1.0f, 0.0f, 0.0f)); //rotate onto y = 0 plane
		
		model_matrix = terrain_mesh_rotate * terrain_mesh_translate; //translate then rotate the mesh

		//Pass the values of the three matrices to the shaders
		glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(proj_matrix_id, 1, GL_FALSE, glm::value_ptr(proj_matrix));

		glDrawElements(
			GL_LINES,
			terrain_indices.size(),
			GL_UNSIGNED_INT,
			(void*)0
		);

		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
	}

	cleanUp();
	return 0;
}
