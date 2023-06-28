NAME := pipex

CC := gcc

# CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
CFLAGS = -Wall -Werror -Wextra -g3
LDFLAGS = -flto -O3 -march=nocona -g3

SRC_DIR	=	./src/

SRC		:=	pipex.c \
			get_next_line.c \
			assign_input.c \
			exit_error_free.c

HEADER = -I ./include -I ../LeakSanitizer 

LIBFT_PRINTF_DIR = ./lib/ft_printf
LIBFT_PRINTF = ./lib/ft_printf/libftprintf.a

libft_printf:
	${MAKE} -C $(LIBFT_PRINTF_DIR) -j

all: libft_printf
	${MAKE} $(NAME) -j

clean:
	${MAKE} -C $(LIBFT_PRINTF_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

leaks:
	@valgrind	--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				--error-limit=no \
				--track-fds=yes \
				--trace-children=yes \
				--tool=memcheck \
				-s -q \
				./pipex infile "kd -l" "wc -l" outfile

.PHONY: libft_printf all clean fclean re

$(NAME):
# $(CC) $(LDFLAGS) $(addprefix $(SRC_DIR),$(SRC)) $(HEADER) $(LIBFT_PRINTF) \
	-o $(NAME)
# $(CC) $(CFLAGS) $(addprefix $(SRC_DIR),$(SRC)) $(HEADER) $(LIBFT_PRINTF) \
	-o $(NAME)
	$(CC) $(LDFLAGS) $(addprefix $(SRC_DIR),$(SRC)) $(HEADER) $(LIBFT_PRINTF) \
	-o $(NAME) -L ../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next
# $(CC) $(CFLAGS) $(addprefix $(SRC_DIR),$(SRC)) $(HEADER) $(LIBFT_PRINTF) \
	-o $(NAME) -L ../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next