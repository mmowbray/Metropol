#version 330

uniform vec3 voxel_Colour;
uniform vec3 camera_position;

out vec4 frag_colour; //This is the final output color used to render the point

void main () {
	frag_colour = vec4(voxel_Colour, 1.0f);
};
