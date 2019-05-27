#ifndef BUILTIN_H
# define BUILTIN_H
# include <string.h>

typedef int	(*t_funptr)(char **tab, t_gcmd *cmd);

int		ft_echo(char **arg, t_gcmd *cmd);
int		ft_cd(char **arg, t_gcmd *cmd);
int		ft_exit(char **arg, t_gcmd *cmd);
//int		ft_env(char **arg, t_gcmd *cmd);
//int		ft_setenv(char **arg, t_gcmd *cmd);
//int		ft_unsetenv(char **arg, t_gcmd *cmd);

typedef struct	s_builtin
{
	char		*name;
	t_funptr	f;
}				t_builtin;

t_builtin		g_builtin_tab[] = { \
	{"echo", &ft_echo},
	{"cd", &ft_cd},
//	{"env", &ft_env},
//	{"setenv", &ft_setenv},
//	{"unsetenv", &ft_unsetenv},
	{"exit", &ft_exit},
	{"end", NULL}
};

#endif