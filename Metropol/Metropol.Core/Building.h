#pragma once

#include "stdafx.h"

#include <vector>
#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "glm.hpp"

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

class Building
{
public:
	Building();
	Building(GLuint programme_id);
	~Building();
	void draw();
	void addPointToVBO(glm::vec3 centre);
private:
	glm::vec3 color;
	GLuint vox_colour_vec3_id, norm_vec3_id;
	glm::vec3 position;
	vector<GLfloat> points;
	vector<GLfloat> left_vertices, right_vertices, top_vertices, bottom_vertices, front_vertices, back_vertices;
	GLuint left_vbo, right_vbo, top_vbo, bottom_vbo, front_vbo, back_vbo;
	GLuint model_matrix_id;
	int height;
	int depth;
	int width;
};