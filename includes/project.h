#ifndef PROJECT_H
# define PROJECT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "../LIB/include/glad/glad.h"
# include <GLFW/glfw3.h>
# include "./get_next_line.h"

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080
# define WIN_NAME	"OpenGL test"

typedef unsigned int	shaderModule_t;
typedef unsigned int	shaderProgram_t;

typedef struct s_data
{
	GLFWwindow	*window;
	shaderProgram_t	shader;
}	t_data;

#endif
