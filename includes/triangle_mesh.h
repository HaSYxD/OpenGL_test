#ifndef TRIANGLE_MESH_H
# define TRIANGLE_MESH_H

typedef struct TriangleMesh
{
	unsigned int	EBO;
	unsigned int	VBO;
	unsigned int	VAO;
	unsigned int	vCount;
}	TriangleMesh;

TriangleMesh	MakeTriangleMesh(void);
void	DrawTriangleMesh(TriangleMesh mesh);
void	DeleteTriangleMesh(TriangleMesh mesh);

#endif
