#ifndef MATERIAL_H
# define MATERIAL_H

typedef struct Material
{
	unsigned int	texture;
}	Material;

Material	MakeMaterial(const char *path);
void	DeleteMaterial(Material material);
void	UseMaterial(Material material, int unit);

#endif