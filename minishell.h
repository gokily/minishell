#ifndef MINISHELL_H
# define MINISHELL_H

# define QUOTE	1
# define SQUOT	1 << 1
# define DQUOT	1 << 2
# define PERMDEN	0
# define NOFILE		1
# define NOCMD		2

# define SHELLESC " ;\"\'\\"
# define DQUOTEESC "$`\"\\\n"

# define ECHOFLAG "neE"
# define ECHOESC "\\abefnrtvc"
# define ECHOE	1
# define ECHON	1 << 1

#include "libft/incl/ft_printf.h"

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

int		ft_find_builtin(char *cmd);
int		ft_serve_builtin(int i, char **cmd_tab, t_gcmd *cmd);

int		ft_add_lcmd(t_gcmd *cmd, char *line, int i);
int		ft_reset_cmd(t_gcmd *cmd);

int		ft_check_quote(char c, int flag);

int						ft_echo_interpret(char **str_tab);
int		ft_error(char *filename, int err_no);


#endif