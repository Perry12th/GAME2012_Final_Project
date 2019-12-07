#version 430 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;
layout(location = 2) in vec2 vertex_texture;
layout(location = 3) in vec3 vertex_normal;

out vec3 Colour;
out vec2 UV;
out vec3 Normal_cameraspace;
out vec3 FragPos_worldspace;

// Values that stay constant for the whole mesh.
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(vertex_position, 1.0f);
	Colour = vertex_colour;
	UV = vertex_texture;
	FragPos_worldspace = (model * vec4(vertex_position, 1.0f)).xyz;

	// Vector that goes from the vertex to the camera, in camera space
	// In camera space, the camera is at the origin (0,0,0)
	//vec3 VertexPosition_cameraspace = vec3(view * model * vec4(vertex_position, 1.0f));
	//vec3 EyeDirection_cameraspace = vec3(0.0f, 0.0f, 0.0f) - VertexPosition_cameraspace;

	// Normal of the vertex in camera space
	Normal_cameraspace = mat3(transpose(inverse(model))) * vertex_normal;

}