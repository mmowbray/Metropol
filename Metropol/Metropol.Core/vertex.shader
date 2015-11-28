#version 330
uniform mat4 view_matrix, model_matrix, proj_matrix;
in vec3 in_Position;
out vec3 frag_Position; //fragment shader requires the fragment positions to deduces the light vector onto the fragment

void main () {
	gl_Position = vec4 (in_Position, 1.0);

	mat4 CTM = proj_matrix * view_matrix * model_matrix;
	frag_Position = vec3(CTM * vec4(frag_Position, 1.0));
};
