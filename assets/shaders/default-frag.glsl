#version 330 core

in vec3 fragmentColor;
in vec2 fragmentTexCoord;

out vec4 screenColor;

uniform sampler2D material;
uniform sampler2D bruh;

void	main()
{
	screenColor = texture(material, fragmentTexCoord);
	float alpha = texture(bruh, fragmentTexCoord).r;
	screenColor *= vec4(fragmentColor, 1.0f);
}