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

	glGenBuffers(1, &vertices_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);

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
	glDeleteBuffers(1, &vertices_vbo);
}

void Tree::insertVoxel(glm::vec3 centre) {

	voxelCount++;

	centre.x = static_cast<int>(centre.x);
	centre.y = static_cast<int>(centre.y);
	centre.z = static_cast<int>(centre.z);

	//@TODO: Code smell!

	//front

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //b
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //d
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	//back

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //b
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //d
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	//left

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //b
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //c
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //c
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //d
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	//right

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //a
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //b
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //d
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //a
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	//top

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //b
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //d
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	vertices.push_back(centre.y + TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	//bottom

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //b
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x + TREE_VOXEL_RADIUS); //c
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //d
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z + TREE_VOXEL_RADIUS);

	vertices.push_back(centre.x - TREE_VOXEL_RADIUS); //a
	vertices.push_back(centre.y - TREE_VOXEL_RADIUS);
	vertices.push_back(centre.z - TREE_VOXEL_RADIUS);
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

	glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(TREE_DRAWING_MODE, 0, vertices.size());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Tree::serialize()
{
	string obj_file = "";

	/* Vertices. */

	for (int i = 0; i < vertices.size(); i += 3)
		obj_file += "v " + std::to_string(vertices.at(i)) + " " + std::to_string(vertices.at(i + 1)) + " " + std::to_string(vertices.at(i + 2)) + "\n";

	/* Faces. */

	int j = 1;

	for (int i = 0; i < vertices.size() / 9; i++)
	{
		obj_file += "f " + std::to_string(j) + "//2 " + std::to_string(j + 1) + "//2 " + std::to_string(j + 2) + "//2\n";
		j += 3;
	}

	/* Save as a .obj file.*/

	ofstream out("Tree.obj");
	out << obj_file;
	out.close();
}
