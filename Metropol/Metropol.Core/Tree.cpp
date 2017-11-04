#include "Tree.h"

#include <string>
#include <fstream>

const GLint TREE_DRAWING_MODE = GL_TRIANGLES;
const float_t TREE_VOXEL_RADIUS = 0.5f;

Tree::Tree(GLuint programme_id)
{
	voxelCount = 0;

	//put tree points

	glm::vec3 startingPoint = glm::vec3(100 / 2, 0, 100 / 2);
	glm::vec3 startingOrientation = glm::vec3(0.0, 1.0, 0.0);

	recursivelyGenerate(100 / 5, startingPoint, startingOrientation, 0);

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

	int xPos = rand() % 130 + 30;
	int zPos = rand() % 130 + 30;

	model_matrix = glm::translate(glm::vec3(-xPos, 0.5f, -zPos));

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
	GLuint buffers[] = { left_vbo, right_vbo, top_vbo, bottom_vbo, front_vbo, back_vbo };
	glDeleteBuffers(6, buffers);
}

void Tree::insertVoxel(glm::vec3 centre) {

	voxelCount++;

	centre.x = static_cast<int>(centre.x);
	centre.y = static_cast<int>(centre.y);
	centre.z = static_cast<int>(centre.z);

	//front

	front_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	front_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	front_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	front_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //b
	front_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	front_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	front_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	front_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	front_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	front_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	front_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	front_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	front_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //d
	front_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	front_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	front_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	front_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	front_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	//back

	back_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	back_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	back_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	back_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //b
	back_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	back_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	back_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	back_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	back_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	back_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	back_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	back_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	back_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //d
	back_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	back_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	back_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	back_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	back_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	//left

	left_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	left_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	left_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	left_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //b
	left_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	left_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	left_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //c
	left_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	left_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	left_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //c
	left_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	left_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	left_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //d
	left_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	left_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	left_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	left_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	left_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	//right

	right_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //a
	right_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	right_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	right_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //b
	right_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	right_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	right_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	right_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	right_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	right_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	right_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	right_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	right_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //d
	right_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	right_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	right_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //a
	right_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	right_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	//top

	top_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	top_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	top_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	top_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //b
	top_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	top_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	top_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	top_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	top_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	top_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	top_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	top_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	top_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //d
	top_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	top_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	top_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	top_vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	top_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	//bottom

	bottom_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	bottom_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	bottom_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	bottom_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //b
	bottom_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	bottom_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	bottom_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	bottom_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	bottom_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	bottom_vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	bottom_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	bottom_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	bottom_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //d
	bottom_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	bottom_vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	bottom_vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	bottom_vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	bottom_vertices.push_back(centre.z - TREE_VOXEL_RADIUS);
}

void Tree::fillPointsBetween2Points(glm::vec3 p1, glm::vec3 p2) {

	glm::vec3 direction = glm::normalize(p2 - p1);

	glm::vec3 currentPosition = p1;

	while (glm::distance(currentPosition, p2) > 1.0f ) {
		insertVoxel(currentPosition);
		currentPosition += direction;
	}
}

void Tree::addBush(glm::vec3 sphere_centre, int bush_radius) {
	for (int x = -bush_radius; x <= bush_radius; x++)
		for (int y = -bush_radius; y <= bush_radius; y++)
			for (int z = -bush_radius; z <= bush_radius; z++)
				if(abs(length(glm::vec3(x, y, z)) - bush_radius) < TREE_VOXEL_RADIUS * 2)
					insertVoxel(glm::vec3(x, y, z) + sphere_centre);
}

void Tree::recursivelyGenerate(float length, glm::vec3 start_point, glm::vec3 orientation, int depth) {

	if (depth == 4)
		return;

	glm::vec3 end_point = start_point + normalize(orientation) * length;

	fillPointsBetween2Points(start_point, end_point);

	depth ? addBush(end_point, 10.0f / depth) : addBush(end_point, 10);

	glm::vec3 new_orientation = glm::rotate(orientation, float(glm::pi<float>()/3.0), glm::cross(orientation, glm::rotateX(orientation, float(glm::pi<float>() / 2))));

	for (int i = 0; i < 3; i++)
	{
		new_orientation = glm::rotate(new_orientation, float(glm::two_pi<float>()/ 3), orientation);
		if (rand() % 2 == 1)
			recursivelyGenerate(length / 1.1, end_point, new_orientation, depth + 1);
	}
}

void Tree::draw()
{
	glUniform3f(vox_colour_vec3_id, color.r, color.g, color.b);
	glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(model_matrix));

	glUniform3f(norm_vec3_id, 0.0f, 0.0f, -1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, front_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(TREE_DRAWING_MODE, 0, front_vertices.size());

	glUniform3f(norm_vec3_id, 0.0f, 0.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, back_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(TREE_DRAWING_MODE, 0, back_vertices.size());

	glUniform3f(norm_vec3_id, -1.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, left_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(TREE_DRAWING_MODE, 0, left_vertices.size());

	glUniform3f(norm_vec3_id, 1.0f, 0.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, right_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(TREE_DRAWING_MODE, 0, right_vertices.size());

	glUniform3f(norm_vec3_id, 0.0f, 1.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, top_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(TREE_DRAWING_MODE, 0, top_vertices.size());

	glUniform3f(norm_vec3_id, 0.0f, -1.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, bottom_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(TREE_DRAWING_MODE, 0, bottom_vertices.size());
}

void Tree::serialize()
{
	string obj_file = "";

	/* Vertices. */

	for (int i = 0; i < front_vertices.size(); i += 3)
		obj_file += "v " + std::to_string(front_vertices.at(i)) + " " + std::to_string(front_vertices.at(i + 1)) + " " + std::to_string(front_vertices.at(i + 2)) + "\n";

	for (int i = 0; i < back_vertices.size(); i += 3)
		obj_file += "v " + std::to_string(back_vertices.at(i)) + " " + std::to_string(back_vertices.at(i + 1)) + " " + std::to_string(back_vertices.at(i + 2)) + "\n";

	for (int i = 0; i < left_vertices.size(); i += 3)
		obj_file += "v " + std::to_string(left_vertices.at(i)) + " " + std::to_string(left_vertices.at(i + 1)) + " " + std::to_string(left_vertices.at(i + 2)) + "\n";

	for (int i = 0; i < right_vertices.size(); i += 3)
		obj_file += "v " + std::to_string(right_vertices.at(i)) + " " + std::to_string(right_vertices.at(i + 1)) + " " + std::to_string(right_vertices.at(i + 2)) + "\n";

	for (int i = 0; i < top_vertices.size(); i += 3)
		obj_file += "v " + std::to_string(top_vertices.at(i)) + " " + std::to_string(top_vertices.at(i + 1)) + " " + std::to_string(top_vertices.at(i + 2)) + "\n";

	for (int i = 0; i < bottom_vertices.size(); i += 3)
		obj_file += "v " + std::to_string(bottom_vertices.at(i)) + " " + std::to_string(bottom_vertices.at(i + 1)) + " " + std::to_string(bottom_vertices.at(i + 2)) + "\n";

	/* Faces. */

	int j = 1;

	for (int i = 0; i < front_vertices.size() / 9; i++)
	{
		obj_file += "f " + std::to_string(j) + "//2 " + std::to_string(j + 1) + "//2 " + std::to_string(j + 2) + "//2\n";
		j += 3;
	}

	for (int i = 0; i < front_vertices.size() / 9; i++)
	{
		obj_file += "f " + std::to_string(j) + "//1 " + std::to_string(j + 1) + "//1 " + std::to_string(j + 2) + "//1\n";
		j += 3;
	}

	for (int i = 0; i < front_vertices.size() / 9; i++)
	{
		obj_file += "f " + std::to_string(j) + "//6 " + std::to_string(j + 1) + "//6 " + std::to_string(j + 2) + "//6\n";
		j += 3;
	}

	for (int i = 0; i < front_vertices.size() / 9; i++)
	{
		obj_file += "f " + std::to_string(j) + "//5 " + std::to_string(j + 1) + "//5 " + std::to_string(j + 2) + "//5\n";
		j += 3;
	}

	for (int i = 0; i < front_vertices.size() / 9; i++)
	{
		obj_file += "f " + std::to_string(j) + "//4 " + std::to_string(j + 1) + "//4 " + std::to_string(j + 2) + "//4\n";
		j += 3;
	}

	for (int i = 0; i < front_vertices.size() / 9; i++)
	{
		obj_file += "f " + std::to_string(j) + "//3 " + std::to_string(j + 1) + "//3 " + std::to_string(j + 2) + "//3\n";
		j += 3;
	}

	/* Save as a .obj file.*/

	ofstream out("Tree.obj");
	out << obj_file;
	out.close();
}
