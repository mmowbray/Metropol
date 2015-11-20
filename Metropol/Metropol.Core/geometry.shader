#version 330 

layout(points) in;
layout(triangle_strip, max_vertices = 30) out;

void create_voxel(vec4 center) 
{
	gl_Position = center + vec4(-1.0,0.0, -1.0, 0.0);
	EmitVertex();

	gl_Position = center + vec4(-1.0, 0.0, -1.0, 0.0);
	EmitVertex();

	gl_Position = center + vec4(-1.0, 80.0, 1.0, 0.0);
	EmitVertex();

	gl_Position = center + vec4(1.0, 0.0, -1.0, 0.0);
	EmitVertex();

	EndPrimitive();

}

void main()
{
	create_voxel(gl_in[0].gl_Position);
}
