#version 330

uniform mat4 view_matrix, model_matrix, proj_matrix;

in vec3 in_Position;
out vec3 frag_Position;

void main () {
	mat4 CTM = proj_matrix * view_matrix * model_matrix;	
	gl_Position = CTM * vec4(in_Position, 1.0);
	frag_Position = vec3(model_matrix * vec4(in_Position, 1));
};
