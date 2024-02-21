#ifndef PROJECT_H
# define PROJECT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../LIB/include/glad/glad.h"
# include <GLFW/glfw3.h>

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080
# define WIN_NAME	"OpenGL test"

typedef struct s_data
{
	GLFWwindow	*window;
}	t_data;

#endif
