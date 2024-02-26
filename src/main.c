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

void	InputHandling(t_data * data)
{
	if (glfwGetKey(data->window, GLFW_KEY_W) == GLFW_PRESS)
		data->camPos[0] += 0.01f;
	else if (glfwGetKey(data->window, GLFW_KEY_S) == GLFW_PRESS)
		data->camPos[0] -= 0.01f;
	if (glfwGetKey(data->window, GLFW_KEY_A) == GLFW_PRESS)
		data->camPos[1] += 0.01f;
	else if (glfwGetKey(data->window, GLFW_KEY_D) == GLFW_PRESS)
		data->camPos[1] -= 0.01f;
	
	if (glfwGetKey(data->window, GLFW_KEY_SPACE) == GLFW_PRESS)
		data->camPos[2] += 0.01f;
	else if (glfwGetKey(data->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		data->camPos[2] -= 0.01f;
}

int	main(void)
{
	TriangleMesh	mesh;
	Material	texture;
	Material	bruh;
	t_data		data;
	
	data.window = InitWindow(WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
	
	
	data.shader = MakeShaderProgram("./assets/shaders/default-vert.glsl", "./assets/shaders/default-frag.glsl");
	
	mesh = MakeTriangleMesh();
	
	texture = MakeMaterial("./assets/image/dfa.jpg");
	bruh = MakeMaterial("./assets/image/bruh.jpg");
	glUseProgram(data.shader);
	
	glUniform1i(glGetUniformLocation(data.shader, "material"), 0);
	glUniform1i(glGetUniformLocation(data.shader, "bruh"), 1);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	
	data.camPos[0] = -0.4f;
	data.camPos[1] = 0.0f;
	data.camPos[2] = 0.2f;
	unsigned int modelLocation = glGetUniformLocation(data.shader, "model");
	unsigned int viewLocation = glGetUniformLocation(data.shader, "view");
	unsigned int projLocation = glGetUniformLocation(data.shader, "projection");
	
	while (!glfwWindowShouldClose(data.window)){
		glfwPollEvents();
		
		InputHandling(&data);
		
		mat4	model = GLM_MAT4_IDENTITY_INIT;
		mat4	view = GLM_MAT4_IDENTITY_INIT;
		mat4	projection = GLM_MAT4_IDENTITY_INIT;
		
		glm_translate(model, (vec3){1.5f, -0.1f, 0.0f});
		glm_rotate(model, (float)glfwGetTime(), (vec3){0.0f, 0.0f, 1.0f});
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, model[0]);
	
		glm_perspective(45, WIN_WIDTH/WIN_HEIGHT, 0.1f, 10, projection);
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, projection[0]);
		
		glm_lookat(data.camPos, (vec3){0.0f, 0.0f, 0.0f}, (vec3){0.0f, 0.0f, 1.0f}, view);
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, view[0]);
		
		
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(data.shader);
		UseMaterial(texture, 0);
		UseMaterial(bruh, 1);
		DrawTriangleMesh(mesh);
		glfwSwapBuffers(data.window);
	}
	DeleteMaterial(texture);
	DeleteMaterial(bruh);
	DeleteTriangleMesh(mesh);
	glDeleteProgram(data.shader);
	glfwTerminate();
	return (0);
}
