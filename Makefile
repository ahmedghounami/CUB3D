NAME	=	cub3D
NAME_BONUS	=	cub3D_bonus

SRC_MANDA	=	Mandatory/cub3d.c Mandatory/cub3d_map.c Mandatory/cub3d_utils.c \
				Mandatory/cub3d_utils2.c Mandatory/cub3d_map2.c Mandatory/ray_casting.c \
				Mandatory/map.c Mandatory/init_exec.c Mandatory/rander_wall.c \
				Mandatory/utils_exec.c Mandatory/hooks.c

SRC_BONUS	=	Bonus/cub3d.c Bonus/cub3d_map.c Bonus/cub3d_utils.c \
				Bonus/cub3d_utils2.c Bonus/cub3d_map2.c Bonus/ray_casting.c \
				Bonus/map.c Bonus/init_exec.c Bonus/mini_map.c Bonus/rander_wall.c \
				Bonus/utils_exec.c Bonus/hooks.c

OBJ_MANDA	=	$(SRC_MANDA:.c=.o)

OBJ_BONUS	=	$(SRC_BONUS:.c=.o)

HEADER_MANDA	=	Mandatory/cub3d.h
HEADER_BONUS	=	Bonus/cub3d.h
CC		=	cc
CFLAGS	=	-Wall -Wextra -fsanitize=address -g
LINKS	=	-Iinclude -lglfw -L/Users/$(USER)/.brew/lib -framework Cocoa -framework OpenGL -framework IOKit 
RM		=	rm -f
LIB		=	./utils/libft.a
MLX		=	../MLX42/build/libmlx42.a

all: $(LIB) $(MLX) $(NAME)

bonus : $(LIB) $(MLX) $(NAME_BONUS)

$(NAME): $(OBJ_MANDA) $(LIB) $(MLX)
	$(CC) $(OBJ_MANDA) $(LIB) $(MLX) $(LINKS) -o $(NAME) -fsanitize=address -g

$(NAME_BONUS): $(OBJ_BONUS) $(LIB) $(MLX)
	$(CC) $(OBJ_BONUS) $(LIB) $(MLX) $(LINKS) -o $(NAME_BONUS) -fsanitize=address -g

Mandatory/%.o: Mandatory/%.c $(HEADER_MANDA)
	$(CC) $(CFLAGS) -c $< -o $@

Bonus/%.o: Bonus/%.c $(HEADER_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	@$(MAKE) -C utils

$(MLX):
	@cd ../MLX42 && cmake -B build && cmake --build build -j4

clean:
	$(MAKE) -C utils clean
	$(RM) $(OBJ_MANDA) $(OBJ_BONUS)

fclean: clean
	$(MAKE) -C utils fclean
	$(RM) $(NAME) $(NAME_BONUS)
	@cd ../MLX42 && rm -rf build

re: fclean all

bre : fclean bonus

