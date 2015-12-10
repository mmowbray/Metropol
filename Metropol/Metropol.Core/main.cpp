/**
Metropol - COMP 371 Fall 2015 Project
main.cpp
Purpose: Entry point of application.

@author Patrick Soueida
@author Maxwell Mowbray
@version M0.1
*/

#include "Building.h"
#include <cstdlib>
#include <ctime>

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
#include <algorithm>
#include <iostream>
#include "Tree.h"

using namespace std;

#define M_PI 3.14159265358979323846264338327950288

GLFWwindow* window = 0x00;
const int DEFAULT_SCREEN_WIDTH = 1280, DEFAULT_SCREEN_HEIGHT = 720;

GLuint shader_programme = 0;
GLuint programme_id;

GLuint vao = 0, terrain_vertices_vbo = 0;

GLuint model_matrix_id = 0;
GLuint view_matrix_id = 0;
GLuint proj_matrix_id = 0;
GLuint vox_colour_vec3_id = 0;
GLuint camera_position_vec3_id = 0;

glm::mat4 model_matrix;
glm::mat4 proj_matrix;
glm::mat4 view_matrix;
GLuint cam_pos_vec3_id = 0; //to broadcast the current camera position to the fragment shader

//camera position vector
glm::vec3 camera_position, camera_direction;

float camera_movement_speed = 5.0f;
float old_mouse_y_pos, old_mouse_x_pos;
float camera_psi = 0.0f, camera_theta = 0.0f;

std::vector<Building> scene_buildings;
std::vector<Tree> scene_trees;

/**
Reacts to mouse input.

@return void.
*/

void cursor_callback(GLFWwindow* window, double xpos, double ypos) {

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

		if (xpos < old_mouse_x_pos)
			camera_psi -= M_PI / 200;

		if (xpos > old_mouse_x_pos)
			camera_psi += M_PI / 200;

		if (ypos > old_mouse_y_pos)
			camera_theta -= M_PI / 200;

		if (ypos < old_mouse_y_pos)
			camera_theta += M_PI / 200;

		camera_theta = glm::clamp(double(camera_theta), (-0.99 * M_PI) / 2.0 ,( 0.99 * M_PI) / 2.0);
		camera_direction = glm::normalize(glm::vec3(sin(camera_psi)*cos(camera_theta), sin(camera_theta), -cos(camera_psi)*cos(camera_theta)));
	}

	old_mouse_x_pos = xpos;
	old_mouse_y_pos = ypos;

}

/**
Reacts to user key input.

@return void.
*/

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (key == GLFW_KEY_W)
		camera_position += camera_direction * camera_movement_speed;
	else if (key == GLFW_KEY_S)
		camera_position -= camera_direction * camera_movement_speed;

	if (key == GLFW_KEY_A)
		camera_position -= glm::cross(camera_direction, glm::vec3(0.0, 1.0, 0.0)) * camera_movement_speed;
	else if (key == GLFW_KEY_D)
		camera_position += glm::cross(camera_direction, glm::vec3(0.0, 1.0, 0.0)) * camera_movement_speed;

	if (key == GLFW_KEY_B && action == GLFW_PRESS)
		scene_buildings.push_back(Building(programme_id));

	if (key == GLFW_KEY_T && action == GLFW_PRESS)
		scene_trees.push_back(Tree(programme_id));

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		scene_buildings.clear();
		scene_trees.clear();
	}
		
}

/**
Updates the vieport and perspective matrix when the window is resized.

@return void.
*/

void framebuffer_size_callback(GLFWwindow* window, int new_screen_width, int new_screen_height)
{
	glViewport(0, 0, new_screen_width, new_screen_height); //update the viewport on window resize

	// Update the Projection matrix after a window resize event
	proj_matrix = glm::perspective(45.0f, float(new_screen_width) / float(new_screen_height), 0.1f, 500.0f);
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
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetKeyCallback(window, key_callback);

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
	camera_position = glm::vec3(0.0f, 10.0f, 0.0f);
	camera_direction= glm::vec3(0.0f, 0.0f, -1.0);

	proj_matrix = glm::perspective(45.0f, float(DEFAULT_SCREEN_WIDTH) / float(DEFAULT_SCREEN_HEIGHT), 0.1f, 500.0f);

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
	programme_id = glCreateProgram();
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
	vox_colour_vec3_id = glGetUniformLocation(programme_id, "voxel_Colour");
	camera_position_vec3_id = glGetUniformLocation(programme_id, "camera_position");

	return programme_id;
}

int main() {

	srand(time(0)); //random number generator seed

	assert(sizeof(glm::vec3) == sizeof(float) * 3 && sizeof(glm::uvec3) == sizeof(unsigned int) * 3);

	initialize();

	glGenVertexArrays(1, &vao);	// Create Vertex Array Object
	glBindVertexArray(vao); //and select it

	std::vector<GLuint> terrain_indices;
	std::vector<GLfloat> terrain_points;

	int terrain_mesh_width = 400, terrain_mesh_height = 400; //terrain mesh dimensions

	terrain_points.push_back(0.0f);
	terrain_points.push_back(0.0f);
	terrain_points.push_back(0.0f);

	terrain_points.push_back(terrain_mesh_width);
	terrain_points.push_back(0.0f);
	terrain_points.push_back(0.0f);

	terrain_points.push_back(terrain_mesh_width);
	terrain_points.push_back(terrain_mesh_height);
	terrain_points.push_back(0.0f);

	terrain_points.push_back(terrain_mesh_width);
	terrain_points.push_back(terrain_mesh_height);
	terrain_points.push_back(0.0f);

	terrain_points.push_back(0.0f);
	terrain_points.push_back(terrain_mesh_height);
	terrain_points.push_back(0.0f);

	terrain_points.push_back(0.0f);
	terrain_points.push_back(0.0f);
	terrain_points.push_back(0.0f);

	glGenBuffers(1, &terrain_vertices_vbo); //generate 1 VBO for the terrain vertices
	glBindBuffer(GL_ARRAY_BUFFER, terrain_vertices_vbo);
	glBufferData(GL_ARRAY_BUFFER, terrain_points.size() * sizeof(GLfloat), &terrain_points.front(), GL_STATIC_DRAW);

	shader_programme = loadShaders("vertex.shader", "fragment.shader");

	GLint posAttrib = glGetAttribLocation(shader_programme, "in_Position"); //enable the position input to the shaders
	glEnableVertexAttribArray(posAttrib);

	glUseProgram(shader_programme);
	glPointSize(4.0);
	
	glm::vec3 terrain_colour = glm::vec3(0.42);

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.851f, 1.0f, 0.988f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//update the camera matrix
		view_matrix = glm::lookAt(
			glm::vec3(camera_position),
			glm::vec3(camera_position + camera_direction),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

		glm::mat4 terrain_mesh_translate = glm::translate(glm::vec3(-(float)terrain_mesh_width / 2, -(float)terrain_mesh_height / 2, 0)); //center the terrain mesh
		glm::mat4 terrain_mesh_rotate = glm::rotate(glm::mat4(), (float)M_PI / 2, glm::vec3(1.0f, 0.0f, 0.0f)); //rotate onto y = 0 plane

		model_matrix = terrain_mesh_rotate * terrain_mesh_translate; //translate then rotate the mesh

		//Pass the values of the three matrices to the shaders
		glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(proj_matrix_id, 1, GL_FALSE, glm::value_ptr(proj_matrix));

		glUniform3f(vox_colour_vec3_id, terrain_colour.r, terrain_colour.g, terrain_colour.b);

		glBindBuffer(GL_ARRAY_BUFFER, terrain_vertices_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(
			GL_TRIANGLES,
			0,
			terrain_points.size()
		);

		for (int i = 0; i < scene_buildings.size(); i++)
		{
			//scene_buildings[i].draw();
		}

		for (int i = 0; i < scene_trees.size(); i++)
		{
			//scene_trees[i].draw();
		}

		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);

	}
	
	cleanUp();
	return 0;
}
