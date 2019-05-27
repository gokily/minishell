#ifndef FT_ENV_H
# define FT_ENV_H

# define ENVFLAG "Ciu"

int		ft_add_envvar(char *var, char **envp);
int     ft_del_envvar(char *var, char **envp);

typedef struct			s_varlst
{
	struct s_pathlst	*next;
	char				*var;
}						t_varlst;

#endif