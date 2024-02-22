#include "../includes/project.h"

void	ExitWithError(const char *str)
{
	printf("[\033[1;31mERROR\033[1;0m]: %s\n", str);
	exit (1);
}

GLFWwindow	*InitWindow(int width, int height, const char *name)
{
	GLFWwindow	*window;
	
	if (!glfwInit())
		ExitWithError("GLFW could not initialize");
	window = glfwCreateWindow(width, height, name, NULL, NULL);
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		glfwTerminate();
		ExitWithError("OpenGL could not initialize");
	}
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	return (window);
}

int	main(void)
{
	TriangleMesh	mesh;
	t_data		data;
	
	data.window = InitWindow(WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	data.shader = MakeShaderProgram("./assets/shaders/default-vert.glsl", "./assets/shaders/default-frag.glsl");
	
	mesh = MakeTriangleMesh();
	
	while (!glfwWindowShouldClose(data.window)){
		glfwPollEvents();
		
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(data.shader);
		DrawTriangleMesh(mesh);
		glfwSwapBuffers(data.window);
	}
	DeleteTriangleMesh(mesh);
	glDeleteProgram(data.shader);
	glfwTerminate();
	return (0);
}
