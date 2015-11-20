#version 330 

layout(points) in;
layout(triangle_strip, max_vertices = 3) out;

void create_voxel(vec4 center) 
{
	gl_Position = center + vec4(-0.1, 0.0, 0.0, 0.0);
	EmitVertex();

	gl_Position = center + vec4(0.1, 7.0, 3.0, 0.0);
	EmitVertex();

	gl_Position = center + vec4(0.1, -20.0, -2.0, 0.0);
	EmitVertex();

	EndPrimitive();
}

void main()
{
	create_voxel(gl_in[0].gl_Position);
}
