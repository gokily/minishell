#ifndef MINISHELL_H
# define MINISHELL_H

# define QUOTE	1
# define SQUOT	1 << 1
# define DQUOT	1 << 2
# define LAST	1 << 3
# define NEW	1 << 4
# define SEMICOL	1 << 5

#include <stdio.h>

typedef struct		s_lcmd
{
	struct s_lcmd	*next;
	int				n;
	char			*cmd;
}					t_lcmd;

typedef struct		s_gcmd
{
	t_lcmd			*head;
	t_lcmd			*end;
	int				flag;
	char			**envp;
}					t_gcmd;


int	ft_search_opening_quote(char *line, t_input *input);
int	ft_search_closing_quote(char *line, t_input *input);

int	ft_add_linput(char *str, t_input *input, int flag);

t_cmd	*ft_cmd_new(void);
int	ft_add_quote_cmd(t_linput *linput, t_cmd *cmd);
int	ft_fill_cmd(char *str, t_cmd *cmd);

//debug
int		print_input(t_input input);

#endif