#include "Building.h"
#define M_PI 3.14159265358979323846264338327950288
const GLint BUILDING_DRAWING_MODE = GL_TRIANGLES;

Building::Building()
{
	
}

void Building::addPointToVBO(glm::vec3 centre)
{
	float width = 0.5f;

	//front

	front_vertices.push_back(centre.x - width);
	front_vertices.push_back(centre.y - width);
	front_vertices.push_back(centre.z - width);

	front_vertices.push_back(centre.x + width);
	front_vertices.push_back(centre.y - width);
	front_vertices.push_back(centre.z - width);

	front_vertices.push_back(centre.x + width);
	front_vertices.push_back(centre.y + width);
	front_vertices.push_back(centre.z - width);

	front_vertices.push_back(centre.x + width);
	front_vertices.push_back(centre.y + width);
	front_vertices.push_back(centre.z - width);

	front_vertices.push_back(centre.x - width);
	front_vertices.push_back(centre.y + width);
	front_vertices.push_back(centre.z - width);

	front_vertices.push_back(centre.x - width);
	front_vertices.push_back(centre.y - width);
	front_vertices.push_back(centre.z - width);

	//back

	back_vertices.push_back(centre.x - width);
	back_vertices.push_back(centre.y - width);
	back_vertices.push_back(centre.z + width);

	back_vertices.push_back(centre.x + width);
	back_vertices.push_back(centre.y - width);
	back_vertices.push_back(centre.z + width);

	back_vertices.push_back(centre.x + width);
	back_vertices.push_back(centre.y + width);
	back_vertices.push_back(centre.z + width);

	back_vertices.push_back(centre.x + width);
	back_vertices.push_back(centre.y + width);
	back_vertices.push_back(centre.z + width);

	back_vertices.push_back(centre.x - width);
	back_vertices.push_back(centre.y + width);
	back_vertices.push_back(centre.z + width);

	back_vertices.push_back(centre.x - width);
	back_vertices.push_back(centre.y - width);
	back_vertices.push_back(centre.z + width);

	//left

	left_vertices.push_back(centre.x - width);
	left_vertices.push_back(centre.y - width);
	left_vertices.push_back(centre.z + width);

	left_vertices.push_back(centre.x - width);
	left_vertices.push_back(centre.y - width);
	left_vertices.push_back(centre.z - width);

	left_vertices.push_back(centre.x - width);
	left_vertices.push_back(centre.y + width);
	left_vertices.push_back(centre.z - width);

	left_vertices.push_back(centre.x - width);
	left_vertices.push_back(centre.y - width);
	left_vertices.push_back(centre.z + width);

	left_vertices.push_back(centre.x - width);
	left_vertices.push_back(centre.y + width);
	left_vertices.push_back(centre.z + width);

	left_vertices.push_back(centre.x - width);
	left_vertices.push_back(centre.y + width);
	left_vertices.push_back(centre.z - width);

	//right

	right_vertices.push_back(centre.x + width);
	right_vertices.push_back(centre.y - width);
	right_vertices.push_back(centre.z + width);

	right_vertices.push_back(centre.x + width);
	right_vertices.push_back(centre.y - width);
	right_vertices.push_back(centre.z - width);

	right_vertices.push_back(centre.x + width);
	right_vertices.push_back(centre.y + width);
	right_vertices.push_back(centre.z - width);

	right_vertices.push_back(centre.x + width);
	right_vertices.push_back(centre.y - width);
	right_vertices.push_back(centre.z + width);

	right_vertices.push_back(centre.x + width);
	right_vertices.push_back(centre.y + width);
	right_vertices.push_back(centre.z + width);

	right_vertices.push_back(centre.x + width);
	right_vertices.push_back(centre.y + width);
	right_vertices.push_back(centre.z - width);

	//top

	top_vertices.push_back(centre.x - width);
	top_vertices.push_back(centre.y + width);
	top_vertices.push_back(centre.z - width);

	top_vertices.push_back(centre.x + width);
	top_vertices.push_back(centre.y + width);
	top_vertices.push_back(centre.z - width);

	top_vertices.push_back(centre.x + width);
	top_vertices.push_back(centre.y + width);
	top_vertices.push_back(centre.z + width);

	top_vertices.push_back(centre.x - width);
	top_vertices.push_back(centre.y + width);
	top_vertices.push_back(centre.z - width);

	top_vertices.push_back(centre.x - width);
	top_vertices.push_back(centre.y + width);
	top_vertices.push_back(centre.z + width);

	top_vertices.push_back(centre.x + width);
	top_vertices.push_back(centre.y + width);
	top_vertices.push_back(centre.z + width);

	//bottom

	bottom_vertices.push_back(centre.x - width);
	bottom_vertices.push_back(centre.y - width);
	bottom_vertices.push_back(centre.z - width);

	bottom_vertices.push_back(centre.x + width);
	bottom_vertices.push_back(centre.y - width);
	bottom_vertices.push_back(centre.z - width);

	bottom_vertices.push_back(centre.x + width);
	bottom_vertices.push_back(centre.y - width);
	bottom_vertices.push_back(centre.z + width);

	bottom_vertices.push_back(centre.x - width);
	bottom_vertices.push_back(centre.y - width);
	bottom_vertices.push_back(centre.z - width);

	bottom_vertices.push_back(centre.x - width);
	bottom_vertices.push_back(centre.y - width);
	bottom_vertices.push_back(centre.z + width);

	bottom_vertices.push_back(centre.x + width);
	bottom_vertices.push_back(centre.y - width);
	bottom_vertices.push_back(centre.z + width);

}

Building::Building(GLuint programme_id)
{
	int width = rand() % 20 + 10;
	int height = rand() % 90 + 20;
	int depth = rand() % 20 + 10;

	for (int x = 0; x < width; x++)
		for (int z = 0; z < depth; z++)
			for (int y = 0; y < height; y++)
				if (x == 0 || y == 0 || z == 0 || x == width - 1 || y == height - 1 || z == depth - 1)
					addPointToVBO(glm::vec3(x, y, z));

	glGenBuffers(1, &front_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, front_vbo);
	glBufferData(GL_ARRAY_BUFFER, front_vertices.size() * sizeof(GLfloat), &front_vertices.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &back_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, back_vbo);
	glBufferData(GL_ARRAY_BUFFER, back_vertices.size() * sizeof(GLfloat), &back_vertices.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &left_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, left_vbo);
	glBufferData(GL_ARRAY_BUFFER, left_vertices.size() * sizeof(GLfloat), &left_vertices.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &right_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, right_vbo);
	glBufferData(GL_ARRAY_BUFFER, right_vertices.size() * sizeof(GLfloat), &right_vertices.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &top_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, top_vbo);
	glBufferData(GL_ARRAY_BUFFER, top_vertices.size() * sizeof(GLfloat), &top_vertices.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &bottom_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, bottom_vbo);
	glBufferData(GL_ARRAY_BUFFER, bottom_vertices.size() * sizeof(GLfloat), &bottom_vertices.front(), GL_STATIC_DRAW);

	model_matrix_id = glGetUniformLocation(programme_id, "model_matrix");
	vox_colour_vec3_id = glGetUniformLocation(programme_id, "voxel_Colour");
	norm_vec3_id = glGetUniformLocation(programme_id, "voxel_Normal");

	int xPos = rand() % (200 - width) + width;
	int zPos = rand() % (200 - depth) + depth;

	position.x = -xPos;
	position.y = 0.5f;
	position.z = -zPos;
	
	int colorType = rand() % 4;

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
		case 3:
			color = glm::vec3(0.89); //silver/white
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

	glUniform3f(norm_vec3_id, 0.0f, 0.0f, -1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, front_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(BUILDING_DRAWING_MODE, 0, front_vertices.size());

	glUniform3f(norm_vec3_id, 0.0f, 0.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, back_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(BUILDING_DRAWING_MODE, 0, back_vertices.size());

	glUniform3f(norm_vec3_id, -1.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, left_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(BUILDING_DRAWING_MODE, 0, left_vertices.size());

	glUniform3f(norm_vec3_id, 1.0f, 0.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, right_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(BUILDING_DRAWING_MODE, 0, right_vertices.size());

	glUniform3f(norm_vec3_id, 0.0f, 1.0f, -1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, top_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(BUILDING_DRAWING_MODE, 0, top_vertices.size());

	glUniform3f(norm_vec3_id, 0.0f, -1.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, bottom_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(BUILDING_DRAWING_MODE, 0, bottom_vertices.size());
}
