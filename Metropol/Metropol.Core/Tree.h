#pragma once

#include "stdafx.h"

#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library

#include "glm.hpp"
#include "transform.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtx/rotate_vector.hpp"

#include <stdio.h>
#include <stdlib.h>

#include <vector>

using namespace std;

class Tree
{
public:
	Tree();
	Tree(GLuint programme_id);
	~Tree();
	void draw();
	void insertVoxel(glm::vec3 point);
	void fillPointsBetween2Points(glm::vec3 p1, glm::vec3 p2);
	void recursivelyGenerate(float length, glm::vec3 position, glm::vec3 orientation, int depth);
	void addBush(glm::vec3 sphere_centre, int size);
private:
	glm::vec3 color;
	std::vector<vector<vector<GLint>>> space;
	GLuint vox_colour_vec3_id, norm_vec3_id;
	glm::vec3 position;
	vector<GLint> points;
	vector<GLfloat> left_vertices, right_vertices, top_vertices, bottom_vertices, front_vertices, back_vertices;
	GLuint left_vbo, right_vbo, top_vbo, bottom_vbo, front_vbo, back_vbo;
	GLuint model_matrix_id;
};