#include "../includes/project.h"

TriangleMesh	MakeTriangleMesh(void)
{
	TriangleMesh	mesh;
	
	mesh.vCount = 6;
	float	data[24] = {
		-1.0f, -1.0f , 0.0f, 1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f , 0.0f, 0.0f, 1.0f, 0.0f,
		-1.0f,  1.0f , 0.0f, 0.0f, 0.0f, 1.0f,
		 1.0f,  1.0f , 0.0f, 1.0f, 1.0f, 1.0f
	};
	
	int	indicesData[6] = {
		0, 1, 2, 2, 1, 3
	};
	
	glGenVertexArrays(1, &mesh.VAO);
	glBindVertexArray(mesh.VAO);
	
	glGenBuffers(1, &mesh.VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
	glBufferData(GL_ARRAY_BUFFER, (6 * mesh.vCount) * sizeof(float), data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void *)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void *)12);
	glEnableVertexAttribArray(1);
	
	
	glGenBuffers(1, &mesh.EBO);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), indicesData, GL_STATIC_DRAW);
	glBindVertexArray(0);
	return (mesh);
}

void	DrawTriangleMesh(TriangleMesh mesh)
{
	glBindVertexArray(mesh.VAO);
	glDrawElements(GL_TRIANGLES, mesh.vCount, GL_UNSIGNED_INT, 0);
}

void	DeleteTriangleMesh(TriangleMesh mesh)
{
	glDeleteVertexArrays(1, &mesh.VAO);
	glDeleteBuffers(1, &mesh.VBO);
	glDeleteBuffers(1, &mesh.EBO);
}
