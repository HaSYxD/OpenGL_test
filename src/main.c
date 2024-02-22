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

char	*GetShaderSource(const char *shaderSrcPath)
{
	static char	*raw;
	char		*buffer;
	int		fd;
	
	memset(raw, 0, ft_strlen(raw));
	fd = open(shaderSrcPath, O_RDONLY);
	if (fd == -1)
		ExitWithError("Shader file could not open");
	while (get_next_line(fd, &buffer) && *buffer != '\0')
	{
		raw = ft_strjoin(raw, buffer);
		free(buffer);
	}
	raw[ft_strlen(raw)] = '\0';
	close(fd);
	return (raw);
}

shaderModule_t	MakeShaderModule(const char *shaderSrcPath, unsigned int module_type)
{
	shaderModule_t	shaderModule;
	const char	*shaderSrc = GetShaderSource(shaderSrcPath);
	
	shaderModule = glCreateShader(module_type);
	glShaderSource(shaderModule, 1, &shaderSrc, NULL);
	glCompileShader(shaderModule);
	
	char	logBuffer[1024];
	int	success;
	
	glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
	if (!success){
		glGetShaderInfoLog(shaderModule, sizeof(logBuffer), NULL, logBuffer);
		ExitWithError(logBuffer);
	}
	return (shaderModule);
}

shaderProgram_t	MakeShaderProgram(const char *vertexSrcPath, const char *fragmentSrcPath)
{
	shaderProgram_t	shader;

	shaderModule_t vShader = MakeShaderModule(vertexSrcPath, GL_VERTEX_SHADER);
	shaderModule_t fShader = MakeShaderModule(fragmentSrcPath, GL_FRAGMENT_SHADER);
	
	shader = glCreateProgram();
	glAttachShader(shader, vShader);
	glAttachShader(shader, fShader);
	glLinkProgram(shader);
	
	char	logBuffer[1024];
	int	success;
	
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success){
		glGetProgramInfoLog(shader, sizeof(logBuffer), NULL, logBuffer);
		ExitWithError(logBuffer);
	}
	
	glDeleteShader(vShader);
	glDeleteShader(fShader);
	
	return (shader);

}

int	main(void)
{
	t_data	data;
	
	data.window = InitWindow(WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	
	data.shader = MakeShaderProgram("./assets/shaders/default-vert.glsl", "./assets/shaders/default-frag.glsl");
	
	while (!glfwWindowShouldClose(data.window)){
		glfwPollEvents();
		
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(data.shader);
		glfwSwapBuffers(data.window);
	}
	glDeleteProgram(data.shader);
	glfwTerminate();
	return (0);
}