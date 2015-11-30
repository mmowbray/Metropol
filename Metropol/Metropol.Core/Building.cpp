#include "Building.h"

Building::Building()
{
	
}

Building::Building(GLuint programme_id)
{
	int width = rand() % 60 + 15;
	int height = rand() % 80 + 15;
	int depth = rand() % 10 + 20;

	for (int x = 0; x < width;x++)
	{
		for (int z = 0; z < depth; z++)
		{
			for (int y = 0; y < height; y++)
			{

				if (x == 0 || y == 0 || z == 0 || x == width-1 || y == height-1 || z == depth-1)
				{
					points.push_back(x);
					points.push_back(y);
					points.push_back(z);
				}

			}
		}
	}

	glGenBuffers(1, &buildingVBO); //generate 1 VBO for the building vertices
	glBindBuffer(GL_ARRAY_BUFFER, buildingVBO);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), &points.front(), GL_STATIC_DRAW);
	model_matrix_id = glGetUniformLocation(programme_id, "model_matrix");

	position.x = -1*rand() % 200;
	position.y = 0.5f;
	position.z = -1 * rand() % 200;
}

Building::~Building()
{

}

void Building::draw()
{

	glm::mat4 position_matrix = glm::translate(position);
	glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(position_matrix));

	printf("position is\:(%f,%f,%f)\n", position.x, position.y, position.z);

	glBindBuffer(GL_ARRAY_BUFFER, buildingVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(
		GL_POINTS,
		0,
		points.size()
	);

}
