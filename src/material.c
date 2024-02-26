#include "../includes/project.h"

Material	MakeMaterial(const char *path)
{
	Material	material;
	unsigned char	*data;
	int		width;
	int		height;
	int		channels;
	
	//Load the texture data with stb library
	data = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
	
	//Create on opengl texture with the data
	glCreateTextures(GL_TEXTURE_2D, 1, &material.texture);
	glBindTexture(GL_TEXTURE_2D, material.texture);
	
	//Send the texture to the graphics card
	glTexImage2D(GL_TEXTURE_2D,
		    0, GL_RGBA, width, height, 0,
		    GL_RGBA, GL_UNSIGNED_BYTE, data);
	
	//Free the data loaded by the library
	stbi_image_free(data);
	
	//Configure sampler
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	return (material);
}

void	DeleteMaterial(Material material)
{
	glDeleteTextures(1, &material.texture);
}

void	UseMaterial(Material material, int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, material.texture);
}
