NAME		= cub3D
SRCDIR		= srcs/
SRC			= parcer.c

SOURCES		= $(addprefix $(SRCDIR),$(SRC))
OBJ			= $(SOURCES:.c=.o)
CC			= gcc
MLXFLAGS	= -lmlx -framework OpenGL -framework AppKit
CFLAGS		= -Iincludes/ -Wall -Wextra -Werror
LIBFT_FLAGS	= -Llibft/ -lft

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ)
			make bonus -C libft/
			$(CC) -o $(NAME) $(MLXFLAGS) $(LIBFT_FLAGS) $(OBJ)

all:		$(NAME)

clean:
			rm -rf $(OBJ)
			make clean -C libft/

fclean:		clean
			rm -rf $(NAME)
			make fclean -C libft/

re:			fclean all

.PHONY:		all clean fclean re