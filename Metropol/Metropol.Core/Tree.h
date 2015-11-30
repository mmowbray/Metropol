﻿#pragma once

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
private:
	std::vector<vector<vector<GLint>>> space;
	glm::vec3 position;
	vector<GLint> points;
	GLuint treeVBO;
	GLuint model_matrix_id;
};