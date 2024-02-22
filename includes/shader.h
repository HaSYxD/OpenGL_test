#ifndef SHADER_H
# define SHADER_H

# include <string.h>
# include <fcntl.h>
# include "./get_next_line.h"

typedef unsigned int	shaderModule_t;
typedef unsigned int	shaderProgram_t;

shaderModule_t		MakeShaderModule(const char *shaderSrcPath, unsigned int module_type);
shaderProgram_t	MakeShaderProgram(const char *vertexSrcPath, const char *fragmentSrcPath);

#endif
