#ifndef PROJECT_H
# define PROJECT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "../LIB/include/glad/glad.h"
# include "../LIB/stb/stb_image.h"
# include "../LIB/cglm/includes/cglm.h"
# include <GLFW/glfw3.h>

# include "./shader.h"
# include "./triangle_mesh.h"
# include "./material.h"
//# include "./matrices.h"

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080
# define WIN_NAME	"OpenGL test"

typedef struct s_data
{
	GLFWwindow		*window;
	shaderProgram_t		shader;
	vec3			camPos;
}	t_data;

void	ExitWithError(const char *str);

#endif
