
#include <unistd.h>
#include <string.h>

void	ft_print_strtab(char **tab)
{
	size_t		i;
	size_t		len;

	i = 0;
	while (tab[i] != NULL)
	{
		len = 0;
		while (tab[i][len] != '\0')
			len++;
		write(STDOUT_FILENO, tab[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}