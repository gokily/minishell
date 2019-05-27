AUTHOR				= gly
NAME				= minishell
CC					= gcc
CFLAGS				= -Wall -Wextra -Werror -g
INC_PATH			= \
	incl/ \
	libft/incl/
INC					= $(addprefix -I, $(INC_PATH))
OBJ_PATH			= obj/
SRC_PATH			= src/
LIBFT				= ./libft/libft.a
LIBFTFLAG			= -lft -L libft

SRC			= \
	main.c	\
	ft_parse_line.c \
	ft_do_cmd.c \
			ft_cmd_handlers.c \
			ft_cmdsplit.c \
			ft_search_path.c \
			ft_exec_cmd.c \
			ft_serve_builtin.c \
			ft_echo.c \
			ft_echo_interpret.c \
			ft_cd.c \
			ft_env.c \
			ft_env_util.c \
			ft_util.c \
			ft_error.c \

OBJ = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))

all	:	$(LIBFT) $(NAME) auteur

$(NAME) : $(OBJ_PATH) $(OBJ)
	$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJ) $(LIBFTFLAG)

$(OBJ_PATH) :
	mkdir -p $@

$(LIBFT) :
	make -C libft
	
$(OBJ_PATH)%.o	: $(SRC_PATH)%.c 
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

auteur:
	echo $(AUTHOR) > auteur

clean :
	make -C libft clean
	/bin/rm -drf $(OBJ_PATH)

fclean : clean
	/bin/rm -f $(NAME) $(LIBFT)

re : fclean all

.PHONY : clean fclean re all