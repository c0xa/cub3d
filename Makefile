NAME		= cub3D
SRCDIR		= srcs/
SRC			= cub3d.c \
			get_next_line_utils.c \
			get_next_line.c \
			initial.c \
			parser_map.c \
			set_parameter.c \
			convert_map.c 

SOURCES		= $(addprefix $(SRCDIR),$(SRC))
OBJ			= $(SOURCES:.c=.o)
CC			= gcc
#MLXFLAGS	= -lmlx -framework OpenGL -framework AppKit
CFLAGS		= -Iinc/ -Wall -Wextra -Werror
LIBFT_FLAGS	= -L libft/ -lft

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ)
			make bonus -C libft/
			cp libft/libft.a $(NAME)
			ar rc $(NAME) $(OBJ)
			#$(CC) -o $(NAME) $(LIBFT_FLAGS) $(OBJ)

all:		$(NAME)


clean:
			rm -rf $(OBJ)
			make clean -C libft/

fclean:		clean
			rm -rf $(NAME)
			make fclean -C libft/

re:			fclean all

.PHONY:		all clean fclean re