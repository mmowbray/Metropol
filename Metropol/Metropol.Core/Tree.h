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
	Tree(GLuint programme_id);
	~Tree();
	int voxelCount;
	glm::mat4 model_matrix;
	void draw();
	void insertVoxel(glm::vec3 point);
	void fillPointsBetween2Points(glm::vec3 p1, glm::vec3 p2);
	void recursivelyGenerate(float length, glm::vec3 position, glm::vec3 orientation, int depth);
	void addBush(glm::vec3 sphere_centre, int bush_radius);
	void serialize();
private:
	glm::vec3 color;
	GLuint vox_colour_vec3_id, norm_vec3_id;
	vector<GLfloat> vertices;
	GLuint vertices_vbo;
	GLuint model_matrix_id;
};
