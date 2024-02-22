#version 330 core

in vec3 fragmentColor;

out vec4 screenColor;

void	main()
{
	vec3 color = vec3(1.0, 1.0, 1.0);
	screenColor = vec4(color, 1.0);
}