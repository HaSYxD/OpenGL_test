NAME = OpenGL_test
SRC = src/main.c\
      src/get_next_line.c\
      src/get_next_line_utils.c\
      LIB/src/glad.c
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -std=c99
RM = rm -f
LIB = -lglfw

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIB)

all: $(NAME)

clean:

	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test:
			@make re
			@make clean
			@clear
			@echo "\033[1;92mDONE !"

