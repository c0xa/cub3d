NAME		= cub3D
SRCDIR		= srcs/
SRC			= parcer.c

SOURCES		= $(addprefix $(SRCDIR),$(SRC))
OBJ			= $(SOURCES:.c=.o)
CC			= gcc
MLXFLAGS	= -l mlx -framework OpenGL -framework AppKit
CFLAGS		= -I inc/ -Wall -Wextra -Werror
LIBFT_FLAGS	= -L libft/ -lft

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