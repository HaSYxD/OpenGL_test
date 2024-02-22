#include "../includes/project.h"

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
