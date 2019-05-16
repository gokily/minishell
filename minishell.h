#ifndef MINISHELL_H
# define MINISHELL_H

# define QUOTE	1
# define SQUOT	1 << 1
# define DQUOT	1 << 2
# define PERMDEN	0
# define NOFILE		1
# define NOCMD		2

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

int		ft_search_path(char *exec_name, char **path, char **envp);

int		ft_exec_cmd_direct(char **cmd_tab, char **envp);
int		ft_exec_cmd_from_path(char **cmd_tab, char *path, char **envp);

int		ft_add_lcmd(t_gcmd *cmd, char *line, int i);
int		ft_reset_cmd(t_gcmd *cmd);

int		ft_error(char *filename, int err_no);


#endif