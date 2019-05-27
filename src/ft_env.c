/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 10:55:09 by gly               #+#    #+#             */
/*   Updated: 2019/05/27 11:20:27 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "ft_printf.h"
#include "minishell.h"
#include "ft_env.h"

static inline int		ft_check_u(char **arg, size_t *i, char **envp, size_t j)
{
	int		status;

	if (arg[*i][j] == '\0')
	{
		status = ft_del_envvar(arg[*i + 1], envp);
		(*i)++;
	}
	else
		status = ft_del_envvar(arg[*i] + j, envp);
	return (status);
}

static inline size_t	ft_check_flag2(char **arg, size_t *i, char **envp,
		size_t j)
{
	int		status;

	status = 0;	
	if (arg[*i][j] == 'i')
	{
		envp = NULL;
		status = ft_check_flag2(arg, i, envp, j + 1);
	}
	else if (arg[*i][j] == 'u')
		status = ft_check_u(arg, i, envp, j + 1);
	else
		ft_printf("env: illegal option -- %c\nusage: env [-i] [-u name]\n\
			[name=value ...] [utility [argument ...]]\n", arg[*i][j]);
	return (status);
}

static inline size_t	ft_check_flag(char **arg, char **envp)
{
	size_t	i;
	int		status;

	i = 0;
	status = 0;
	while (arg[i] != NULL)
	{	
		if (arg[i][0] == '-')
			status = ft_check_flag2(arg, &i, envp, 1);
		i++;
	}
	return (i);
}
static inline int		ft_check_var(char **arg, size_t *i, char **envp)
{
	if (arg[*i] == NULL)
		return (0);
	while (arg[*i] != NULL && ft_strchr(arg[*i], '='))
	{
		if (ft_add_envvar(arg[*i], envp) == -1)
			return (-1);
		(*i)++;
	}
	return (0);
}

int		ft_env(char **arg, t_gcmd *cmd)
{
	size_t	i;
	char	**envp;

	pid_t	pid;
	pid_t	wpid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (!(envp = ft_cpy_strtab((const char **)cmd->envp)))
			return (-1);
		i = ft_check_flag(arg, envp);
		if (ft_check_var(arg, &i, envp) == -1)
			return (-1);
		ft_do_cmd(cmd);
		return (0);
	}
	wpid = waitpid(pid, &status, WUNTRACED);
	if (wpid == -1)
		write(STDOUT_FILENO, "WPID ERROR\n", 11);
	return (status);
}