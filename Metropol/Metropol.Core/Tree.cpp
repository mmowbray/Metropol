#include "Tree.h"

#define M_PI 3.14159265358979323846264338327950288
#include <iostream>

Tree::Tree()
{

}

void Tree::insertVoxel(glm::vec3 point) {

	int x_index = static_cast<int>(point.x);
	int y_index = static_cast<int>(point.y);
	int z_index = static_cast<int>(point.z);

	points.push_back(x_index);
	points.push_back(y_index);
	points.push_back(z_index);

}

void Tree::fillPointsBetween2Points(glm::vec3 p1, glm::vec3 p2) {

	glm::vec3 direction = glm::normalize(p2 - p1);
	glm::vec3 currentPosition = p1;

	while (glm::distance(currentPosition, p2) > 4.0f ) {
		insertVoxel(currentPosition);
		currentPosition += direction;
	}

}

void Tree::addBush(glm::vec3 sphere_centre, int radius) {

	for (int x = 0; x < 100; x++)
	{
		for (int z = 0; z < 100; z++)
		{
			for (int y = 0; y < 100; y++)
			{
				glm::vec3 current_pos = glm::vec3(x, y, z);
				if (pow((current_pos.x - sphere_centre.x), 2) + pow((current_pos.y - sphere_centre.y), 2) + pow((current_pos.z - sphere_centre.z), 2) - pow(radius, 2) < 10.0)
				{
					insertVoxel(current_pos);
				}
			}
		}
	}
}

void Tree::recursivelyGenerate(float length, glm::vec3 start_point, glm::vec3 orientation, int depth) {

	if (depth == 4)
		return;

	glm::vec3 end_point = start_point + normalize(orientation) * length;

	fillPointsBetween2Points(start_point, end_point);

	if (depth == 0)
		addBush(end_point, 10); 
	else
		addBush(end_point, 15 * (9/(9*(depth+1))));

	glm::vec3 new_orientation = glm::rotate(orientation, float(M_PI/3.0), glm::cross(orientation, glm::rotateX(orientation, float(M_PI/2))));

	for (int i = 0; i < 3; i++)
	{
		new_orientation = glm::rotate(new_orientation, float(2 * M_PI / 3), orientation);
		if (rand() % 2 == 0)
			recursivelyGenerate(length / 1.1, end_point, new_orientation, depth + 1);
	}

}

Tree::Tree(GLuint programme_id)
{
	int dimension = rand() % 60 + 15;

	//put tree points

	glm::vec3 startingPoint = glm::vec3(100 / 2, 0, 100 / 2); //rather use dimension here
	glm::vec3 startingOrientation = glm::vec3(0.0, 1.0, 0.0);

	recursivelyGenerate(100/5, startingPoint, startingOrientation, 0);

	glGenBuffers(1, &treeVBO); //generate 1 VBO for the building vertices
	glBindBuffer(GL_ARRAY_BUFFER, treeVBO);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLint), &points.front(), GL_STATIC_DRAW);
	model_matrix_id = glGetUniformLocation(programme_id, "model_matrix");
	vox_colour_vec3_id = glGetUniformLocation(programme_id, "voxel_Colour");

	int xPos = rand() % 160 + 30;
	int zPos = rand() % 160 + 30;

	position.x = -1 * xPos;
	position.y = -0.5f;
	position.z = -1 * zPos;

	int colorType = rand() % 5;

	switch (colorType)
	{
		case 0:
			color = glm::vec3(0.2, 0.5, 0.2); //green1
			break;
		case 1:
			color = glm::vec3(0.4, 0.7, 0.1); //green2
			break;
		case 2:
			color = glm::vec3(0.2, 0.9, 0.23); //green3
			break;
		case 3:
			color = glm::vec3(0.96, 0.72, 0.0); //autumn orange
			break;
		case 4:
			color = glm::vec3(0.69, 0.13, 0.13); //autumn red
			break;
		default:
			break;
	}
}

Tree::~Tree()
{

}

void Tree::draw()
{
	glUniform3f(vox_colour_vec3_id, color.r, color.g, color.b);

	glm::mat4 position_matrix = glm::translate(position);
	glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(position_matrix));
	glBindBuffer(GL_ARRAY_BUFFER, treeVBO);
	glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, 0, 0);
	glDrawArrays(
		GL_POINTS,
		0,
		points.size()
	);
}
