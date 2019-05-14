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
	char			*rst;
	char			**envp;
}					t_gcmd;

int		ft_parse_line(char *line, t_gcmd *cmd);
char			**ft_cmdsplit(const char *s);
int		ft_do_cmd(t_gcmd *cmd);

int		ft_add_lcmd(t_gcmd *cmd, char *line, int i);
int		ft_reset_cmd(t_gcmd *cmd);


#endif