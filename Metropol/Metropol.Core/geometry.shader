#version 330 

uniform mat4 view_matrix, model_matrix, proj_matrix;

layout(points) in;
layout(triangle_strip, max_vertices = 100) out;

out vec3 out_Normal;

void create_voxel(vec4 center, mat4 CTM) 
{
	float size = 0.5;

	out_Normal = vec3(0.0, 0.0, -1.0);
	//4
	gl_Position = CTM * (center + vec4(size, -size, size, 1.0)); EmitVertex();

	//3
	gl_Position = CTM * (center + vec4(-size, -size, size, 1.0)); EmitVertex();

	//7
	gl_Position = CTM * (center + vec4(size, -size, -size, 1.0)); EmitVertex();

	out_Normal = vec3(0.0, 0.0, -1.0);
	//3
	gl_Position = CTM * (center + vec4(-size, -size, size, 1.0)); EmitVertex();

	//7
	gl_Position = CTM * (center + vec4(size, -size, -size, 1.0)); EmitVertex();

	//8
	gl_Position = CTM * (center + vec4(-size, -size, -size, 1.0)); EmitVertex();

	out_Normal = vec3(0.0, 1.0, 0.0);
	//7
	gl_Position = CTM * (center + vec4(size, -size, -size, 1.0)); EmitVertex();

	//8
	gl_Position = CTM * (center + vec4(-size, -size, -size, 1.0)); EmitVertex();

	//5
	gl_Position = CTM * (center + vec4(-size, size, -size, 1.0)); EmitVertex();

	out_Normal = vec3(-1.0, 0.0, 0.0);
	//8
	gl_Position = CTM * (center + vec4(-size, -size, -size, 1.0)); EmitVertex();

	//5
	gl_Position = CTM * (center + vec4(-size, size, -size, 1.0)); EmitVertex();

	//3
	gl_Position = CTM * (center + vec4(-size, -size, size, 1.0)); EmitVertex();

	out_Normal = vec3(-1.0, 0.0, 0.0);
	//5
	gl_Position = CTM * (center + vec4(-size, size, -size, 1.0)); EmitVertex();

	//3
	gl_Position = CTM * (center + vec4(-size, -size, size, 1.0)); EmitVertex();
	
	//1
	gl_Position = CTM * (center + vec4(-size, size, size, 1.0)); EmitVertex();
	
	out_Normal = vec3(0.0, -1.0, 0.0);
	//3
	gl_Position = CTM * (center + vec4(-size, -size, size, 1.0)); EmitVertex();
	
	//1
	gl_Position = CTM * (center + vec4(-size, size, size, 1.0)); EmitVertex();
	
	//4
	gl_Position = CTM * (center + vec4(size, -size, size, 1.0)); EmitVertex();

	out_Normal = vec3(0.0, -1.0, 0.0);
	//1
	gl_Position = CTM * (center + vec4(-size, size, size, 1.0)); EmitVertex();
	
	//4
	gl_Position = CTM * (center + vec4(size, -size, size, 1.0)); EmitVertex();
	
	//2
	gl_Position = CTM * (center + vec4(size, size, size, 1.0)); EmitVertex();
	
	out_Normal = vec3(1.0, 0.0, 0.0);
	//4
	gl_Position = CTM * (center + vec4(size, -size, size, 1.0)); EmitVertex();
	
	//2
	gl_Position = CTM * (center + vec4(size, size, size, 1.0)); EmitVertex();

	//7
	gl_Position = CTM * (center + vec4(size, -size, -size, 1.0)); EmitVertex();

	out_Normal = vec3(1.0, 0.0, 0.0);
	//2
	gl_Position = CTM * (center + vec4(size, size, size, 1.0)); EmitVertex();

	//7
	gl_Position = CTM * (center + vec4(size, -size, -size, 1.0)); EmitVertex();
	
	//6
	gl_Position = CTM * (center + vec4(size, size, -size, 1.0)); EmitVertex();

	out_Normal = vec3(0.0, 1.0, 0.0);
	//7
	gl_Position = CTM * (center + vec4(size, -size, -size, 1.0)); EmitVertex();
	
	//6
	gl_Position = CTM * (center + vec4(size, size, -size, 1.0)); EmitVertex();
	
	//5
	gl_Position = CTM * (center + vec4(-size, size, -size, 1.0)); EmitVertex();

	out_Normal = vec3(0.0, 0.0, 1.0);
	//6
	gl_Position = CTM * (center + vec4(size, size, -size, 1.0)); EmitVertex();
	
	//5
	gl_Position = CTM * (center + vec4(-size, size, -size, 1.0)); EmitVertex();
	
	//2
	gl_Position = CTM * (center + vec4(size, size, size, 1.0)); EmitVertex();

	out_Normal = vec3(0.0, 0.0, 1.0);
	//5
	gl_Position = CTM * (center + vec4(-size, size, -size, 1.0)); EmitVertex();
	
	//2
	gl_Position = CTM * (center + vec4(size, size, size, 1.0)); EmitVertex();
	
	//1
	gl_Position = CTM * (center + vec4(-size, size, size, 1.0)); EmitVertex();
	
	EndPrimitive();
}

void main()
{
	mat4 CTM = proj_matrix * view_matrix * model_matrix;
	create_voxel(gl_in[0].gl_Position, CTM);



}
