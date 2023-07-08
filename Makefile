NAME := pipex

CC := gcc

# CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -flto -O3 -march=nocona -g

SRC_DIR	=	./src/

SRC		:=	cmds.c \
			exit_error_free.c \
			get_next_line.c \
			infile_outfile.c \
			main.c \
			pid_funcs.c \
			pipex.c

HEADER = -I ./include -I ../LeakSanitizer 

LIBFT_PRINTF_DIR = ./lib/ft_printf
LIBFT_PRINTF = ./lib/ft_printf/libftprintf.a

libft_printf:
	${MAKE} -C $(LIBFT_PRINTF_DIR) -j

all: libft_printf
	${MAKE} $(NAME) -j

bonus: all

clean:
	${MAKE} -C $(LIBFT_PRINTF_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

leaks:
	@valgrind	--leak-check=full \
				--show-leak-kinds=all \
				--track-fds=yes \
				--trace-children=yes \
				./pipex infile "cat" "grep PATH" outfile
	
# -q \
# --tool=memcheck \
# --track-origins=yes \
# --error-limit=no \
# ./pipex infile "cat" "grep PATH" "grep usr/" "wc -c" outfile
# ./pipex infile "cat" "grep PATH" "grep usr/" outfile
# ./pipex infile "kd -l" "wc -l" outfile

.PHONY: libft_printf all clean fclean re bonus leaks

$(NAME):
# $(CC) $(LDFLAGS) $(addprefix $(SRC_DIR),$(SRC)) $(HEADER) $(LIBFT_PRINTF) \
	-o $(NAME)
	$(CC) $(CFLAGS) $(addprefix $(SRC_DIR),$(SRC)) $(HEADER) $(LIBFT_PRINTF) \
	-o $(NAME)
# $(CC) $(LDFLAGS) $(addprefix $(SRC_DIR),$(SRC)) $(HEADER) $(LIBFT_PRINTF) \
	-o $(NAME) -L ../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next
# $(CC) $(CFLAGS) $(addprefix $(SRC_DIR),$(SRC)) $(HEADER) $(LIBFT_PRINTF) \
	-o $(NAME) -L ../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next