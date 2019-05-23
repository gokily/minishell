#include <stdlib.h>
#include "libft.h"
#include "ft_env.h"

int		ft_add_varlst(char *var, t_env* env)
{
	t_varlst	*elem;

	if (!(elem = malloc(sizeof(t_varlst))))
		return (-1);
	if (!(elem->var = ft_strdup(var)))
		return (-1);
	if (env->varlst != NULL)
		elem->next = env->varlst;
	else
		elem->next = NULL;
	env->varlst = elem;
	return (0);
}