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
	~Building();
	void draw();
private:
	glm::vec3 color;
	glm::mat4 locationModelMatrix;
	vector<GLfloat> points;
	GLuint vao;
	GLuint buildingVBO;
};