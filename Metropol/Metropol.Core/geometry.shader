/*
Taken from:
http://www.geeks3d.com/20111111/simple-introduction-to-geometry-shaders-glsl-opengl-tutorial-part1/

This is just a test
*/
#version 330 

layout(points) in;
layout(triangle_strip, max_vertices = 3) out;

void main()
{
	for (int i = 0; i<3; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}















