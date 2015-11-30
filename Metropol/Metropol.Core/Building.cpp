#include "Building.h"

Building::Building()
{
	
}

Building::Building(GLuint programme_id)
{
	int width = rand() % 20 + 10;
	int height = rand() % 60 + 10;
	int depth = rand() % 20 + 10;

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
	vox_colour_vec3_id = glGetUniformLocation(programme_id, "voxel_Colour");

	int xPos = rand() % (200 - width) + width;
	int zPos = rand() % (200 - depth) + depth;

	position.x = -1 * xPos;
	position.y = 0.5f;
	position.z = -1 * zPos;
	
	int colorType = rand() % 3;

	switch (colorType)
	{
		case 0:
			color = glm::vec3(0.212); //dark grey
			break;
		case 1:
			color = glm::vec3(0.561); //light grey
			break;
		case 2:
			color = glm::vec3(0.361, 0.251, 0.2); //brown
			break;
		default:
			break;
	}
}

Building::~Building()
{

}

void Building::draw()
{
	glUniform3f(vox_colour_vec3_id, color.r, color.g, color.b);

	glm::mat4 position_matrix = glm::translate(position);
	glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(position_matrix));
	glBindBuffer(GL_ARRAY_BUFFER, buildingVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(
		GL_POINTS,
		0,
		points.size()
	);

}
