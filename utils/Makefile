NAME	=	libft.a
SRC		=	ft_strlen.c ft_memcpy.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
			ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_putchar_fd.c \
			ft_putstr_fd.c get_next_line.c get_next_line_utils.c
OBJS	=	$(SRC:.c=.o)
LIBC	=	ar -rcs
CFLAGS	=	-Wall -Wextra -Werror
CC		=	cc
RM		=	rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[0;36mMaking libft\033[0m"
	@$(LIBC) $(NAME) $(OBJS)

%.o: %.c libft.h
	@echo "\033[0;32mCompiling libft objects\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@echo "\033[0;31mCleaning libft\033[0m"
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re