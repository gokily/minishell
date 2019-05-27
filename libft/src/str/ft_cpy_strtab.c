#include <stdlib.h>

char	**ft_cpy_strtab(const char **src)
{
	char	**dest;
	size_t	i;

	if (src == NULL || *src == NULL)
		return (NULL);
	i = 0;
	while (src[i] != NULL)
		i++;
	if (!(dest = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	dest[i] = NULL;
	i = 0;
	while (src[i] != NULL)
	{
		dest[i] = (char *)src[i];
		i++;
	}
	return (dest);
}