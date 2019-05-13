NAME	=	minishell

SRC		=	main.c	\
			ft_parse_line.c \
			ft_do_cmd.c \
			ft_cmd_handlers.c \

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
	
%.o : %.c ./minishell.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	make -C libft clean
	/bin/rm -f $(OBJ)

fclean : clean
	/bin/rm -f $(NAME) $(LIBFT)

re : fclean all

.PHONY : clean fclean re all