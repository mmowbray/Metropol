#include "Tree.h"

#define M_PI 3.14159265358979323846264338327950288

Tree::Tree()
{

}

void recursivelyGenerate(float length, glm::vec3 position, glm::vec3 orientation, int depth) {

	if (depth == 3)
		return;

	glm::vec3 end_point = position + normalize(orientation) * length;
	glm::vec3 new_orientation = orientation;

	glm::vec4 temp = glm::vec4(new_orientation, 1.0);
	temp = glm::rotate(glm::mat4(), 0.4f, glm::cross(orientation, glm::vec3(1))) * temp;
	
	new_orientation.x = temp.x;
	new_orientation.y = temp.y;
	new_orientation.z = temp.z;

	for (int i = 0; i < 3; i++)
	{		
		/*new_orientation = glm::rotate(orientation, i * M_PI * 2, orientation );
		recursivelyGenerate(length / 2, end_point, new_orientation, depth + 1);*/

		glm::vec4 temp2 = glm::vec4(new_orientation, 1.0);
		temp2 = glm::rotate(glm::mat4(), float(i * M_PI * 2.0f), orientation) * temp2;

		new_orientation.x = temp2.x;
		new_orientation.y = temp2.y;
		new_orientation.z = temp2.z;

		recursivelyGenerate(length / 2, end_point, new_orientation, depth + 1);

	}

}

void Tree::insertVoxel(glm::vec3 point) {
	space[int(point.x)][int(point.y)][int(point.z)] = 1;
}

void Tree::fillPointsBetween2Points(glm::vec3 p1, glm::vec3 p2) {

	glm::vec3 direction = glm::normalize(p2 - p1);
	glm::vec3 currentPosition = p1;

	while (glm::distance(p1, p2) > 2.0f) {

		insertVoxel(currentPosition);
		currentPosition += direction;

	}

}

Tree::Tree(GLuint programme_id)
{
	int dimension = rand() % 60 + 15;
	
	space[100][100][100]; //rather use dimension here

	//put tree points

	glm::vec3 startingPoint = glm::vec3(100 / 2, 0, 100 / 2); //rather use dimension here
	glm::vec3 startingOrientation = glm::vec3(0.0, 1.0, 0.0);

	recursivelyGenerate(100 / 2, startingPoint, startingOrientation, 0);

	//fill vbo with tree points

	for (int x = 0; x < 100; x++)
	{
		for (int z = 0; z < 100; z++)
		{
			for (int y = 0; y < 100; y++)
			{

				if (space[x][y][z] == 1)
				{
					points.push_back(x);
					points.push_back(y);
					points.push_back(z);
				}

			}
		}
	}

	glGenBuffers(1, &treeVBO); //generate 1 VBO for the building vertices
	glBindBuffer(GL_ARRAY_BUFFER, treeVBO);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), &points.front(), GL_STATIC_DRAW);
	model_matrix_id = glGetUniformLocation(programme_id, "model_matrix");

	position.x = -1 * rand() % 200;
	position.y = 0.5f;
	position.z = -1 * rand() % 200;
}

Tree::~Tree()
{

}

void Tree::draw()
{
	glm::mat4 position_matrix = glm::translate(position);
	glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(position_matrix));
	glBindBuffer(GL_ARRAY_BUFFER, treeVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(
		GL_POINTS,
		0,
		points.size()
	);
}
