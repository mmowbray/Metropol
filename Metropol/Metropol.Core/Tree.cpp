#include "Tree.h"

#define M_PI 3.14159265358979323846264338327950288
#include <iostream>

Tree::Tree()
{

}

void Tree::insertVoxel(glm::vec3 point) {
	//space.at(int(point.x)).at(int(point.y)).at(int(point.z)) = 1;

	int x_index = static_cast<int>(point.x);
	int y_index = static_cast<int>(point.y);
	int z_index = static_cast<int>(point.z);

	if (x_index > 99)
		x_index = 99;

	if (y_index > 99)
		y_index = 99;

	if (z_index > 99)
		z_index = 99;

	space.at(x_index).at(z_index).at(y_index) = 1;
}

void Tree::fillPointsBetween2Points(glm::vec3 p1, glm::vec3 p2) {

	glm::vec3 direction = glm::normalize(p2 - p1);
	glm::vec3 currentPosition = p1;

	while (glm::distance(currentPosition, p2) > 2.0f ) {
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

void Tree::recursivelyGenerate(float length, glm::vec3 position, glm::vec3 orientation, int depth) {

	if (depth == 3)
		return;

	glm::vec3 end_point = position + normalize(orientation) * length;

	fillPointsBetween2Points(position, end_point);
	//addBush(end_point,  pow(9, 1/(depth+1))); //exponential
	if ((depth + 1) == 1)
		addBush(end_point, 7); 
	else
		addBush(end_point, 15 * (9/(9*(depth+1)))); //linear

	glm::vec3 new_orientation1 = orientation;

	glm::vec4 temp = glm::vec4(new_orientation1, 1.0);
	temp = glm::rotate(glm::mat4(), float(M_PI/3), glm::cross(orientation, glm::vec3(1.0, 2.0, 5.0))) * temp;

	new_orientation1.x = temp.x;
	new_orientation1.y = temp.y;
	new_orientation1.z = temp.z;

	/*new_orientation = glm::rotate(orientation, i * M_PI * 2, orientation );
	recursivelyGenerate(length / 2, end_point, new_orientation, depth + 1);*/

	recursivelyGenerate(length / 3, end_point, new_orientation1, depth + 1);

	glm::vec4 temp2 = glm::vec4(new_orientation1, 1.0);
	temp2 = glm::rotate(glm::mat4(), float(1.0/3.0 * M_PI * 2.0f), orientation) * temp2;

	glm::vec3 new_orientation2;
	new_orientation2.x = temp2.x;
	new_orientation2.y = temp2.y;
	new_orientation2.z = temp2.z;

	recursivelyGenerate(length / 3, end_point, new_orientation2, depth + 1);

	temp2 = glm::vec4(new_orientation1, 1.0);
	temp2 = glm::rotate(glm::mat4(), float(2.0 / 3.0 * M_PI * 2.0f), orientation) * temp2;

	glm::vec3 new_orientation3;
	new_orientation3.x = temp2.x;
	new_orientation3.y = temp2.y;
	new_orientation3.z = temp2.z;

	recursivelyGenerate(length / 3, end_point, new_orientation3, depth + 1);

}

Tree::Tree(GLuint programme_id)
{
	int dimension = rand() % 60 + 15;
	
	//space[100][100][100]; //rather use dimension here	

	for (int x = 0; x < 100; x++)
	{
		std::vector<vector<int>> new_row;
		space.push_back(new_row);

		for (int z = 0; z < 100; z++)
		{
			std::vector<int> new_row2;
			space.at(x).push_back(new_row2);

			for (int y = 0; y < 100; y++)
			{
				space.at(x).at(z).push_back(0);
			}
		}
	}
	//put tree points

	glm::vec3 startingPoint = glm::vec3(100 / 2, 0, 100 / 2); //rather use dimension here
	glm::vec3 startingOrientation = glm::vec3(0.0, 1.0, 0.0);

	recursivelyGenerate(100 / 4, startingPoint, startingOrientation, 0);

	//fill vbo with tree points

	for (int x = 0; x < 100; x++)
	{
		for (int z = 0; z < 100; z++)
		{
			for (int y = 0; y < 100; y++)
			{

				if (space.at(x).at(z).at(y) == 1)
				{
					
					points.push_back(x);
					points.push_back(y);
					points.push_back(z); 

				}

				//printf("current tree voxel: %i,%i,%i\n", x, y, z);

			}
		}
	}

	glGenBuffers(1, &treeVBO); //generate 1 VBO for the building vertices
	glBindBuffer(GL_ARRAY_BUFFER, treeVBO);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLint), &points.front(), GL_STATIC_DRAW);
	model_matrix_id = glGetUniformLocation(programme_id, "model_matrix");

	position.x = 0.0f;
	position.y = 10.5f;
	position.z = 0.0f;
}

Tree::~Tree()
{

}

void Tree::draw()
{
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
