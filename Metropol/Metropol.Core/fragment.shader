#version 330

//uniform vec3 cam_pos;

//in vec3 out_Normal;
//in vec3 frag_Position;

out vec4 frag_colour; //This is the final output color used to render the point

void main () {

	/*vec3 light_position = vec3(0.0, 5.0, 15.0); //the location of the light in world coordinates
	vec3 light_colour = vec3(0.5, 0.4, 0.3); //the colour of the light (yellow)
	vec3 object_colour = texture2D(texture_sampler, out_UV).rgb; //cube fragment colour at that point

	// ambient lighting involves simply setting a base colour that all fragments start off at, regardless of other conditions.
	float ambient_strength = 0.12f;
	vec3 ambient_contribution = ambient_strength * light_colour;

	// diffuse lighting involves analyzing the angle between the light ray hitting the fragment and the normal of that fragment (Lambertian)
	vec3 norm = normalize(out_Normal); //ensure the fragment's normal vector is of length 1
	vec3 light_direction = normalize(light_position - frag_Position); //the light ray vector goes from the fragment to the light (so we do light_position - frag_position, not the other way around)
	float incident_degree = max(dot(norm, light_direction), 0.0); //intensity of incidence of light ray with face
	vec3 diffuse_contribution = incident_degree * light_colour; //portion of the light added by diffuse lighting

	vec3 resultant_colour = (ambient_contribution + diffuse_contribution) * object_colour;*/

	frag_colour = vec4(0.5, 0.4, 0.7, 1.0);
	//frag_colour = vec4(resultant_colour, 1.0f);
};
