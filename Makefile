NAME := pipex

CC := gcc

# CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
CFLAGS = -Wall -Werror -Wextra -g
# LDFLAGS = -flto -O3 -march=nocona -g

SRC_DIR	=	./src/

SRC		:=	cmds.c \
			exit_error_free.c \
			get_next_line.c \
			infile_outfile.c \
			main.c \
			pid_funcs.c

HEADER = -I ./include -I ../LeakSanitizer 

LIBFT_PRINTF_DIR = ./lib/ft_printf
LIBFT_PRINTF = ./lib/ft_printf/libftprintf.a

all: libft_printf
	${MAKE} $(NAME) -j

libft_printf:
	${MAKE} -C $(LIBFT_PRINTF_DIR) -j

bonus: all

clean:
	${MAKE} -C $(LIBFT_PRINTF_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

leaks:
	@valgrind	--track-fds=yes \
				--track-origins=yes \
				--tool=memcheck \
				--trace-children=yes \
				--leak-check=full \
				--show-leak-kinds=all \
				-s \
				./pipex infile "cat" "grep PATH" "grep /usr" outfile

.PHONY: libft_printf all clean fclean re bonus leaks

$(NAME):

# $(CC) $(CFLAGS) $(addprefix $(SRC_DIR),$(SRC)) $(HEADER) $(LIBFT_PRINTF) \
	-o $(NAME) -L ../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next
# $(CC) $(LDFLAGS) $(addprefix $(SRC_DIR),$(SRC)) $(HEADER) $(LIBFT_PRINTF) \
	-o $(NAME)
	$(CC) $(CFLAGS) $(addprefix $(SRC_DIR),$(SRC)) $(HEADER) $(LIBFT_PRINTF) \
	-o $(NAME)
# $(CC) $(LDFLAGS) $(addprefix $(SRC_DIR),$(SRC)) $(HEADER) $(LIBFT_PRINTF) \
	-o $(NAME) -L ../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next


# -q \
# --error-limit=no \
# ./pipex infile "cat" "grep PATH" "grep usr/" "wc -c" outfile
# ./pipex infile "cat" "grep PATH" "grep usr/" outfile
# ./pipex infile "kd -l" "wc -l" outfile