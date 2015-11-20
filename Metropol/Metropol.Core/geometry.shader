#version 330 

layout(points) in;
layout(points, max_vertices = 3) out;

void main()
{
	for (int i = 0; i<3; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}
