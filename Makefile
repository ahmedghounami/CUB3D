NAME			=	cub3D
NAME_BONUS		=	cub3D_bonus

SRC				=	cub3d.c \
					_Parsing/mandatory/parsing1.c _Parsing/mandatory/parsing2.c _Parsing/mandatory/parsing_utils1.c _Parsing/mandatory/parsing_utils2.c \
					_Execution/mandatory/execution.c _Execution/mandatory/key_pressed.c _Execution/mandatory/ray_casting.c \
					_Execution/mandatory/render.c _Execution/mandatory/execution_utils.c \
					Utils/error.c
SRC_BONUS		=	cub3d_bonus.c \
					_Parsing/bonus/parsing1_bonus.c _Parsing/bonus/parsing2_bonus.c _Parsing/bonus/parsing_utils1_bonus.c _Parsing/bonus/parsing_utils2_bonus.c \
					_Execution/bonus/execution_bonus.c _Execution/bonus/key_pressed_bonus.c _Execution/bonus/ray_casting_bonus.c \
					_Execution/bonus/render_bonus.c _Execution/bonus/mini_map_bonus.c _Execution/bonus/animation_bonus.c \
					_Execution/bonus/execution_utils_bonus.c Utils/error_bonus.c

OBJS			=	$(SRC:.c=.o)
OBJS_BONUS		=	${SRC_BONUS:_bonus.c=_bonus.o}

HEADER			=	includes/cub3d.h
HEADER_BONUS	=	includes/cub3d_bonus.h

CC				=	cc
RM				=	rm -f
LIB				=	Utils/libft.a
CFLAGS			=	-Wall -Wextra -Werror
MLX				=	../MLX42/build/libmlx42.a
LINKS			=	-Iinclude -lglfw -L/Users/$(USER)/.brew/lib -framework Cocoa -framework OpenGL -framework IOKit

all: libft $(MLX) $(NAME)

bonus: libft $(MLX) $(NAME_BONUS)

$(NAME): $(OBJS) $(LIB) $(MLX)
	@echo "\033[0;36mMaking cub3D\033[0m"
	@$(CC) $(OBJS) $(LIB) $(MLX) $(LINKS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS) $(LIB) $(MLX)
	@echo "\033[0;36mMaking cub3D_bonus\033[0m"
	@$(CC) $(OBJS_BONUS) $(LIB) $(MLX) $(LINKS) -o $(NAME_BONUS)

libft:
	@cd Utils && make

$(MLX):
	@echo "\033[0;33mMaking MLX\033[0m"
	@cd ../MLX42 && cmake -B build && cmake --build build -j4

%_bonus.o: %_bonus.c $(HEADER_BONUS)
	@echo "\033[0;32mCompiling bonus\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c $(HEADER)
	@echo "\033[0;32mCompiling mandatory\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@echo "\033[0;34mCleaning\033[0m"
	@$(MAKE) -C Utils clean
	@$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	@echo "\033[0;31mFull Cleaning\033[0m"
	@cd Utils && make fclean
	@$(RM) $(NAME) $(NAME_BONUS)
	@cd ../MLX42 && rm -rf build

re: fclean all
