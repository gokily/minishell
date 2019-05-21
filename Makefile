NAME	=	minishell

SRC		=	main.c	\
			ft_parse_line.c \
			ft_do_cmd.c \
			ft_cmd_handlers.c \
			ft_cmdsplit.c \
			ft_search_path.c \
			ft_exec_cmd.c \
			ft_serve_builtin.c \
			ft_echo.c \
			ft_echo_interpret.c \
			ft_util.c \
			ft_error.c \

OBJ		=	$(SRC:.c=.o)

CC		=	gcc

CFLAGS	=	-g -Wall -Wextra -Werror

LIBFT	=	./libft/libft.a

LIBFTFLAG	=	-lft -L libft

all	:	$(LIBFT) $(NAME) 

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFTFLAG)
	
$(LIBFT) :
	make -C libft
	
%.o : %.c ./minishell.h ./builtin.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	make -C libft clean
	/bin/rm -f $(OBJ)

fclean : clean
	/bin/rm -f $(NAME) $(LIBFT)

re : fclean all

.PHONY : clean fclean re all