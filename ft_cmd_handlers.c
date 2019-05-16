#include <stdlib.h>
#include "libft/incl/libft.h"
#include "minishell.h"

static inline t_lcmd	*ft_lcmd_new(char *cmd_str)
{
	t_lcmd	*lcmd;

	if (!(lcmd = malloc(sizeof(t_lcmd))))
		return (NULL);
	lcmd->n = 0;
	if (!(lcmd->cmd = cmd_str))
		return (NULL);
	lcmd->next = NULL;
	return (lcmd);
}

static inline void	ft_lcmd_push(t_lcmd *elem, t_gcmd *cmd)
{
	if (cmd->head == NULL)
	{
		cmd->head = elem;
		cmd->end = elem;
	}
	else
	{
		cmd->end->next = elem;
		cmd->end = elem;
	}
}

int		ft_add_lcmd(t_gcmd *cmd, char *line, int i)
{
	t_lcmd	*elem;
	char	*cmd_str;
	
	cmd_str = cmd->rst != NULL ? ft_strjoinfree(cmd->rst, ft_strndup(line, i),
		LEFT | RIGHT) : ft_strndup(line, i);
	cmd->rst = NULL;
	if (cmd_str == NULL)
		return (-1);
	if (!(elem = ft_lcmd_new(cmd_str)))
		return (-1);
	ft_lcmd_push(elem, cmd);
	return (0);
}

int		ft_reset_cmd(t_gcmd *cmd)
{
	t_lcmd	*elem;
	t_lcmd	*tmp;

	if (cmd->head == NULL)
		return (0);
	elem = cmd->head;
	while (elem != NULL)
	{
		tmp = elem->next;
		ft_memdel((void **)&(elem->cmd));
		ft_memdel((void **)&(elem));
		elem = tmp;
	}
	cmd->head = NULL;
	cmd->end = NULL;
	cmd->flag = 0; //Pas sur pour celui la.
	return (0);
}

















/*
int	ft_add_quote_lcmd(t_linput *linput, t_cmd *cmd)
{
	t_lcmd	*elem;

	if (cmd->flag & SEMICOL || cmd->head == NULL)
	{
		if (!(elem = ft_lcmd_new()))
			return (0);
		if (!(elem->cmd = ft_strndup(linput->str + 1,
			ft_strlen(linput->str + 1) - 1)))
			return (0);
		ft_lcmd_push(elem, cmd);
		cmd->flag ^= SEMICOL;
	}
	else 
	{
		elem = cmd->end;
		if (elem->arg == NULL)
		{
			if (!(elem->arg = ft_strdup(linput->str)))
				return (0);
		}
		else if (!(elem->arg = ft_strjoinfree(elem->arg,
			ft_strdup(linput->str), LEFT | RIGHT)))
			return (0);
	}
	return (1);
}

int	ft_fill_cmd(char *str, t_cmd *cmd)
{
	t_lcmd	*elem;
	char	*pos;

	if (cmd->flag & SEMICOL || cmd->head == NULL)
	{
		if (!(elem = ft_lcmd_new()))
			return (0);
		pos = ft_strchr(str, ' ');
		n = pos == NULL ? ft_strlen(str) : pos - str;
		if (!(elem->cmd = ft_strndup(str, n)))
			return (0);
		ft_lcmd_push(elem, cmd);
		cmd->flag ^= SEMICOL;
	}
}*/