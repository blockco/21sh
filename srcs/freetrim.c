#include "../headers/minishell.h"

int		findspacefree(char *s)
{
	int	i;

	i = 0;
	while (s[i] <= ' ' && s[i])
		i++;
	return (i);
}

char	*ft_freetrim(char *s)
{
	unsigned	i;
	unsigned	start;
	unsigned	end;
	char		*new;

	i = findspacefree((char*)s);
	start = i;
	while (s[i])
		i++;
	while (s[i] <= ' ' && i > start)
		i--;
	end = i;
	new = ft_strnew(end - start + 1);
	i = 0;
	if (!new)
		return (NULL);
	while (start <= end)
	{
		new[i] = s[start];
		start++;
		i++;
	}
	new[i] = '\0';
	free(s);
	return (new);
}
