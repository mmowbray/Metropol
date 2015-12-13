#version 330

uniform vec3 voxel_Colour;
uniform vec3 voxel_Normal;
uniform vec3 camera_position;

in vec3 frag_Position;
out vec4 frag_colour;

void main () {
	vec3 light_colour = vec3(0.5, 0.4, 0.2); //the colour of the light (yellow)
	vec3 light_position = vec3(0.0f, 100.0f, 0.0f);

	vec3 norm = normalize(voxel_Normal); //ensure the fragment's normal vector is of length 1
	vec3 light_direction = normalize(light_position - frag_Position);
	float incident_degree = max(dot(norm, light_direction), 0.0); //intensity of incidence of light ray with face
	float diffuse_intensity = 0.50f;
	vec3 diffuse_contribution = incident_degree * light_colour * diffuse_intensity; //portion of the light added by diffuse lighting

	//the final colour takes contributions from all 3 local lighting techniques
	vec3 resultant_colour = voxel_Colour + diffuse_contribution;

	//clamp the rgb values to not go over 1.0
	resultant_colour.r = min(1.0, resultant_colour.r);
	resultant_colour.g = min(1.0, resultant_colour.g);
	resultant_colour.b = min(1.0, resultant_colour.b);

	frag_colour = vec4(resultant_colour, 1.0f);
};
