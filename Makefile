NAME = minishell
CC = cc
SRCS =		srcs/main.c \
		srcs/utils.c \
		srcs/env.c \
				
		
LIBFT = ./libft/libft.a
INCLUDES = -Iincludes
OBJECTS = $(SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra -g $(INCLUDES)
LFLAGS = -L./libft -lft

all : $(NAME)

$(NAME): $(OBJECTS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME) $(LFLAGS) -lreadline

$(LIBFT):
	make -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) -g -c $< -o $@

clean:
	$(RM) $(OBJECTS)

fclean:	clean
	$(RM) $(NAME)
	make fclean -C ./libft


re: fclean all

.PHONY: all clean fclean re

