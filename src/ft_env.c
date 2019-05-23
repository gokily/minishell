#include "libft.h"
#include "minishell.h"
#include "ft_env.h"

static inline int		ft_check_c(char **arg, size_t *i, t_env *env)
{
	if (arg[*i][2] == '\0')
	{
		env->dir = ft_strdup(arg[*i + 1]);
		*i++;
	}
	else
		env->dir = ft_strdup(arg[*i] + 2);
	return (env->dir == NULL ? -1 : 0);
}

static inline int		ft_check_u(char **arg, size_t *i, t_env *env)
{
	int		status;

	if (arg[*i][2] == '\0')
	{
		status = ft_add_varlst(arg[*i + 1], env);
		*i++;
	}
	else
		status = ft_add_varlst(arg[*i] + 2, env);
	return (status);
}

static inline size_t	ft_check_flag2(char **arg, int *i, t_gcmd *cmd,
	t_env *env, int j)
{
	int		status;

	status = 0;	
	if (arg[i][1] == 'i')
		cmd->envp = NULL;
	else if (arg[i][1] == 'C')
		status = ft_check_c(arg, &i, env);
	else if (arg[i][1] == 'u')
		status = ft_check_u(arg, &i, env);
	if (status == -1)
		return (-1);

}
static inline size_t	ft_check_flag(char **arg, t_gcmd *cmd, t_env *env)
{
	size_t	i;
	int		status;

	i = 0;
	status = 0;
	while (arg[i] != NULL)
	{	
		if (arg[i][0] == '-')
		{
			status = ft_check_flag2(arg, &i, cmd, env, 1);
		
		}
		i++;
	}
	return (i);
}

t_env	*ft_env_new(void)
{
	t_env	*env;

	if (!(env = malloc(sizeof(env))))
		return (NULL);
	env->int = 0;
	env->varlst = NULL;
	env->dir = NULL;
	return (env);
}

int		ft_env(char **arg, t_gcmd *cmd)
{
	size_t	i;
	t_env	*env;

	if (!(env = ft_env_new()))
		return (-1);
	i = ft_check_flag(arg, cmd, env);
}