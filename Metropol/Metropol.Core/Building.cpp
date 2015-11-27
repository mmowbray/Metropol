#include "Building.h"

Building::Building()
{
	for (int z = 0; z < 20; z++)
	{
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				points.push_back(x);
				points.push_back(y);
				points.push_back(z);

			}
		}
	}

	//glGenVertexArrays(1, &vao);	// Create Vertex Array Object
	//glBindVertexArray(vao); //and select it

	glGenBuffers(1, &buildingVBO); //generate 1 VBO for the building vertices
	glBindBuffer(GL_ARRAY_BUFFER, buildingVBO);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), &points.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

Building::~Building()
{

}

void Building::draw()
{
	//glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, buildingVBO);

	glDrawElements(
		GL_POINTS,
		points.size(),
		GL_UNSIGNED_INT,
		(void*)0
		);
}