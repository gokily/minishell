/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:31:41 by gly               #+#    #+#             */
/*   Updated: 2019/02/22 09:24:33 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/incl/libft.h"
#include "minishell.h"

static int		ft_count_word(const char *s)
{
	size_t	nb;
	size_t	i;
	int		flag;

	nb = 0;
	i = 0;
	flag = 0;
	while (s[i] != '\0')
	{
		if ((flag & DQUOT) && !(ft_strncmp("\\\"", s + i, 2)))
				i += 2;
		flag = ft_check_quote(s[i], flag);
		if (!(flag & QUOTE))
		{
			if (s[i] == '\\' && ft_strchr(SHELLESC, s[i + 1]))
				i++;
			if ((i == 0 && s[i] != ' ' && s[i] != '\0')
				|| (s[i] == ' ' && s[i + 1] != ' ' && s[i + 1] != '\0'))
				nb++;			
		}
		i++;
	}
	return (nb);
}

size_t			ft_elem_length(const char *s)
{
	size_t	i;
	char	c;

	i = 0;
	c = 0;
	while (*s != '\0')
	{
		if (c == 0 && *s == '\\' && *(s + 1) != '\0')
		{
			i++;
			s++;
		}
		else if (*s == ' ' && c == 0)
			return (i);
		else if ((*s == '\"' || *s == '\'') && (c == 0 || *s == c))
			c = c == 0 ? *s : 0;
		else if (c != 0)
		{
			if (c == '\"' && *s == '\\' && ft_strchr(DQUOTEESC, *(s + 1)))
				s++;
			i++;
		}
		else
			i++;
		s++;
	}
	return (i);
}

size_t			ft_fill_tab_elem(char *elem, const char *s, size_t i)
{
	size_t		j;
	char		c;

	j = 0;
	c = 0;
	elem[i] = '\0';
	while (i != 0)
	{
		if (c == 0 && *s == '\\')
		{
			s++;
			*elem = *s;
			i--;
			elem++;
			j++;
		}
		else if (*s == ' ' && c == 0)
			return (i);
		else if ((*s == '\"' || *s == '\'') && (c == 0 || *s == c))
			c = c == 0 ? *s : 0;
		else if (c != 0)
		{
			if (c == '\"' && *s == '\\' && ft_strchr(DQUOTEESC, *(s + 1)))
				s++;
			*elem = *s;
			i--;
			elem++;
		}
		else
		{
			*elem = *s;
			i--;
			elem++;
		}

		s++;
		j++; 
	}
	return (j + (c != 0 ? 1 : 0));
}

char			**ft_cmdsplit(const char *s)
{
	size_t	n;
	char	**tab;
	size_t	i;
	size_t	j;

	if (s == 0)
		return (0);
	if (!(tab = malloc(sizeof(*tab) * (ft_count_word(s) + 1))))
		return (0);
	n = 0;
	while (*s != '\0')
	{
		while (*s == ' ')
			s++;
		i = ft_elem_length(s);
		if (!(tab[n] = malloc(sizeof(char) * (i + 1))))
			return (NULL);
		j = ft_fill_tab_elem(tab[n], s, i);
		n++;
		s += j;
	}
	tab[n] = 0;
	return (tab);
}
