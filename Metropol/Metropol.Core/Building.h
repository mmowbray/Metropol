#pragma once

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

using namespace std;

class Building
{
public:
	Building();
	Building(GLuint programme_id);
	~Building();
	void draw();
private:
	glm::vec3 color;
	GLuint vox_colour_vec3_id;
	glm::vec3 position;
	vector<GLfloat> points;
	GLuint buildingVBO;
	GLuint model_matrix_id;
	int height;
	int depth;
	int width;
};