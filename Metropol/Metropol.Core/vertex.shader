#version 330

//uniform mat4 view_matrix, model_matrix, proj_matrix;	

in vec3 in_Position;

void main () {
	//mat4 CTM = proj_matrix * view_matrix * model_matrix;
	gl_Position = vec4 (in_Position, 1.0);
};
