#include "../headers/minishell.h"

char *join_free_front(char *front, char *back)
{
	char *ret;
	int i;
	int a;

	ret = ft_strnew(ft_strlen(front) + ft_strlen(back));
	a = 0;
	i = 0;
	while(front[i])
	{
		ret[a] = front[i];
		a++;
		i++;
	}
	i = 0;
	while (back[i])
	{
		ret[a] = back[i];
		a++;
		i++;
	}
	free(front);
	return (ret);
}
