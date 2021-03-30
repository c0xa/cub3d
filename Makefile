NAME		= cub3D
SRCDIR		= srcs/
SRC			= cub3d.c \
			get_next_line_utils.c \
			get_next_line.c \
			initial.c \
			parser_cub.c \
			set_parameter.c \
			convert_map.c \
			check_error_map.c \
			draw.c \
			assistant_draw.c \
			check_button.c \
			engine.c \
			init_position.c \
			texture.c \
			motion.c \
			draw_and_sort_sprites.c \
			save.c 

SOURCES		= $(addprefix $(SRCDIR),$(SRC))
OBJ			= $(SOURCES:.c=.o)
CC			= gcc
MLXFLAGS	= -lmlx -framework OpenGL -framework AppKit
CFLAGS		= -Iinc/ -Wall -Wextra -Werror
LIBFT_FLAGS	= -L libft/ -lft

.c.o:
			$(CC) $(CFLAGS) -g -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ)
			make bonus -C libft/
			$(CC) -g -o $(NAME) $(LIBFT_FLAGS) $(MLXFLAGS) $(OBJ)

all:		$(NAME)

bonus:		$(OBJ)
			make bonus -C libft/
			$(CC) -g -o $(NAME) $(LIBFT_FLAGS) $(MLXFLAGS) $(OBJ)

clean:
			rm -rf $(OBJ)
			make clean -C libft/

fclean:		clean
			rm -rf $(NAME)
			make fclean -C libft/

re:			fclean all

.PHONY:		all clean fclean re