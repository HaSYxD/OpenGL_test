#version 330 core

layout (location=0) in vec3 vertexPos;
layout (location=1) in vec3 vertexColor;

out vec3 fragmentColor;
out vec2 fragmentTexCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void	main()
{
	gl_Position = projection * view * model * vec4(vertexPos, 1.0);
	fragmentColor = vertexColor;
	fragmentTexCoord = vec2(vertexPos.x * 0.5f, vertexPos.y * -0.5f) - 0.5f;
}