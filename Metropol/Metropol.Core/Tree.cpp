#include "Tree.h"

#define M_PI 3.14159265358979323846264338327950288
#include <iostream>

Tree::Tree()
{

}

Tree::~Tree()
{

}

void Tree::insertVoxel(glm::vec3 centre) {

	centre.x = static_cast<int>(centre.x);
	centre.y = static_cast<int>(centre.y);
	centre.z = static_cast<int>(centre.z);

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

void Tree::fillPointsBetween2Points(glm::vec3 p1, glm::vec3 p2) {

	glm::vec3 direction = glm::normalize(p2 - p1);
	glm::vec3 currentPosition = p1;

	while (glm::distance(currentPosition, p2) > 1.0f ) {
		insertVoxel(currentPosition);
		currentPosition += direction;
	}

}

void Tree::addBush(glm::vec3 sphere_centre, int radius) {

	for (int x = sphere_centre.x - radius; x <= sphere_centre.x + radius; x++)
	{
		for (int z = sphere_centre.z - radius; z <= sphere_centre.z + radius; z++)
		{
			for (int y = sphere_centre.y - radius; y <= sphere_centre.y + radius; y++)
			{
				glm::vec3 current_pos = glm::vec3(x, y, z);
				if (pow((current_pos.x - sphere_centre.x), 2) + pow((current_pos.y - sphere_centre.y), 2) + pow((current_pos.z - sphere_centre.z), 2) - pow(radius, 2) < 5.0)
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
	else if (rand() % 2 == 1)
		addBush(end_point, 1.0f / depth);

	glm::vec3 new_orientation = glm::rotate(orientation, float(M_PI/3.0), glm::cross(orientation, glm::rotateX(orientation, float(M_PI/2))));

	for (int i = 0; i < 3; i++)
	{
		new_orientation = glm::rotate(new_orientation, float(2 * M_PI / 3), orientation);
		if (rand() % 2 == 1)
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

	int xPos = rand() % 160 + 30;
	int zPos = rand() % 160 + 30;

	position.x = -1 * xPos;
	position.y = 5.0f;
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

void Tree::draw()
{
	glUniform3f(vox_colour_vec3_id, color.r, color.g, color.b);

	glm::mat4 position_matrix = glm::translate(position);
	glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(position_matrix));

	glUniform3f(norm_vec3_id, 0.0f, 0.0f, -1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, front_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, front_vertices.size());

	glUniform3f(norm_vec3_id, 0.0f, 0.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, back_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, back_vertices.size());

	glUniform3f(norm_vec3_id, -1.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, left_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, left_vertices.size());

	glUniform3f(norm_vec3_id, 1.0f, 0.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, right_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, right_vertices.size());

	glUniform3f(norm_vec3_id, 0.0f, 1.0f, -1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, top_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, top_vertices.size());

	glUniform3f(norm_vec3_id, 0.0f, -1.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, bottom_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, bottom_vertices.size());
}
