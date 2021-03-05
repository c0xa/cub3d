NAME		= cub3D
SRCDIR		= srcs/
LIBFT_DIR   = libft/
LIBFT       = libft.a
SRC			= get_next_line.c \
				get_next_line_utils.c \
				cub3d.c \
				parse_map.c \
				error.c \
				initial.c \
				parse_file.c 

SOURCES		= $(addprefix $(SRCDIR),$(SRC))
OBJ			= $(SOURCES:.c=.o)
CC			= gcc
#MLXFLAGS	= -lmlx -framework OpenGL -framework AppKit
CFLAGS		= -Iinc/ -Wall -Wextra -Werror
LIBFT_FLAGS	= -L libft/ -lft

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ)
			make bonus -C $(LIBFT_DIR)
			cp $(LIBFT_DIR)$(LIBFT) $(NAME)
			ar rc $(NAME) $(OBJ)
			#$(CC) -o $(NAME) $(MLXFLAGS) $(LIBFT_FLAGS) $(OBJ)

all:		$(NAME)


clean:
			rm -rf $(OBJ)
			make clean -C libft/

fclean:		clean
			rm -rf $(NAME)
			make fclean -C libft/

re:			fclean all

.PHONY:		all clean fclean re
