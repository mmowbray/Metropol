#include "Building.h"

Building::Building()
{
	
}

Building::Building(GLuint programme_id)
{
	int xMax = rand() % 60 + 15;
	int yMax = rand() % 60 + 15;
	int zMax = rand() % 100 + 20;

	for (int z = -zMax; z < 0; z++)
	{
		for (int y = 0; y < yMax; y++)
		{
			for (int x = 0; x < xMax; x++)
			{
				points.push_back(x);
				points.push_back(y);
				points.push_back(z);
			}
		}
	}

	glGenBuffers(1, &buildingVBO); //generate 1 VBO for the building vertices
	glBindBuffer(GL_ARRAY_BUFFER, buildingVBO);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), &points.front(), GL_STATIC_DRAW);
	model_matrix_id = glGetUniformLocation(programme_id, "locationModelMatrix");

	position.x = rand() % 1 + 200;
	position.y = rand() % 1 + 200;
	position.z = 0.0f;
}

Building::~Building()
{

}

void Building::draw()
{

	glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(glm::translate(position)));
	glBindBuffer(GL_ARRAY_BUFFER, buildingVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(
		GL_POINTS,
		0,
		points.size()
	);

}