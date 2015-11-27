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

	glGenBuffers(1, &buildingVBO); //generate 1 VBO for the building vertices
	glBindBuffer(GL_ARRAY_BUFFER, buildingVBO);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), &points.front(), GL_STATIC_DRAW);

}

Building::~Building()
{

}

void Building::draw()
{

	glBindBuffer(GL_ARRAY_BUFFER, buildingVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(
		GL_POINTS,
		0,
		points.size()
	);

}