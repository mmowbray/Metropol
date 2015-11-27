#version 330 

layout(points) in;
layout(triangle_strip, max_vertices = 15) out;
uniform mat4 view_matrix, model_matrix, proj_matrix;

void create_voxel(vec4 center, mat4 CTM) 
{
	float size = 0.14;
	//4
	gl_Position = CTM * (center + vec4(size, -size, size, 1.0));
	EmitVertex();

	//3
	gl_Position = CTM * (center + vec4(-size, -size, size, 1.0));
	EmitVertex();

	//7
	gl_Position = CTM * (center + vec4(size, -size, -size, 1.0));
	EmitVertex();

	//8
	gl_Position = CTM * (center + vec4(-size, -size, -size, 1.0));
	EmitVertex();

	//5
	gl_Position = CTM * (center + vec4(-size, size, -size, 1.0));
	EmitVertex();

	//3
	gl_Position = CTM * (center + vec4(-size, -size, size, 1.0));
	EmitVertex();

	//1
	gl_Position = CTM * (center + vec4(-size, size, size, 1.0));
	EmitVertex();

	//4
	gl_Position = CTM * (center + vec4(size, -size, size, 1.0));
	EmitVertex();

	//2
	gl_Position = CTM * (center + vec4(size, size, size, 1.0));
	EmitVertex();

	//7
	gl_Position = CTM * (center + vec4(size, -size, -size, 1.0));
	EmitVertex();

	//6
	gl_Position = CTM * (center + vec4(size, size, -size, 1.0));
	EmitVertex();

	//5
	gl_Position = CTM * (center + vec4(-size, size, -size, 1.0));
	EmitVertex();

	//2
	gl_Position = CTM * (center + vec4(size, size, size, 1.0));
	EmitVertex();

	//1
	gl_Position = CTM * (center + vec4(-size, size, size, 1.0));
	EmitVertex();

	EndPrimitive();

}

void main()
{
	mat4 CTM = proj_matrix * view_matrix * model_matrix;
	create_voxel(gl_in[0].gl_Position, CTM);
}
