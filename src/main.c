#include "../includes/project.h"

void	ExitWithError(const char *str)
{
	printf("[\033[1;31mERROR\033[1;0m]: %s\n", str);
	exit (1);
}

GLFWwindow	*InitWindow(int with, int height, const char *name)
{
	GLFWwindow	*window;
	
	if (!glfwInit())
		ExitWithError("GLFW could not initialize");
	window = glfwCreateWindow(with, height, name, NULL, NULL);
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		glfwTerminate();
		ExitWithError("OpenGL could not initialize");
	}
	return (window);
}

int	main(void)
{
	t_data	data;
	
	data.window = InitWindow(WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(data.window)){
		glfwPollEvents();
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(data.window);
	}
	glfwTerminate();
	return (0);
}