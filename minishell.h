#ifndef MINISHELL_H
# define MINISHELL_H

# define QUOTE	1
# define SQUOT	1 << 1
# define DQUOT	1 << 2
# define LAST	1 << 3
# define NEW	1 << 4

#include <stdio.h>


typedef struct		s_lcmd
{
	struct s_lcmd	*next;
	int				flag;
	char			*str;
}					t_lcmd;

typedef struct		s_cmd
{
	int		flag;
	t_lcmd	*head;
	t_lcmd	*end;
	char	**envp;
}					t_cmd;

int	ft_search_opening_quote(char *line, t_cmd *cmd);
int	ft_search_closing_quote(char *line, t_cmd *cmd);

int	ft_add_lcmd(char *str, t_cmd *cmd, int flag);


//debug
int		print_cmd(t_cmd cmd);

#endif