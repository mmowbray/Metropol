#version 330 

layout(points) in;
layout(triangle_strip, max_vertices = 10) out;

void create_voxel(vec4 center) 
{
	gl_Position = center + vec4(-0.2f, -0.4f, 0.0f, 0.0f);    // 1:bottom-left
	EmitVertex();
	gl_Position = center + vec4(0.2f, -0.14f, 0.0f, 0.0f);    // 2:bottom-right
	EmitVertex();
	gl_Position = center + vec4(-0.2f, 0.4f, 0.0f, 0.0f);    // 3:top-left
	EmitVertex();
	gl_Position = center + vec4(0.2f, 0.2f, 0.0f, 0.0f);    // 4:top-right
	EmitVertex();

	EndPrimitive();

}

void main()
{
	create_voxel(gl_in[0].gl_Position);
}
