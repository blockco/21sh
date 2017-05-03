#include "../headers/minishell.h"

char	**ft_tdnew(int size)
{
	char **ret;
	int i;

	i = 0;
	ret = (char**)malloc(sizeof(char*) + 1);
	while(i <= size)
	{
		ret[i] = NULL;
		i++;
	}
	return ret;
}

char	**ft_realloc2(char **arr)
{
	char	**newy;
	int		size;
	int		i;
	int		j;

	size = 0;
	i = -1;
	j = -1;
	while (arr && arr[size])
		size++;
	newy = ft_tdnew(size + 1);
	newy[size + 1] = 0;
	newy[size] = 0;
	while (arr && arr[++i] != 0)
		newy[i] = ft_strdup(arr[i]);
	while (arr && arr[++j])
		free(arr[j]);
	return (newy);
}

char	**twsplit(char *str)
{
	int		i;
	char	**newt;

	i = 0;
	newt = NULL;
	while (str && str[i])
	{
		if (str[i] == 34 || str[i] == 39 || str[i] == 96 ||
				str[i] == 40 || str[i] == 91)
			newt = split_quotes(str, newt, &i);
		else if (str[i] != ' ' && str[i] != '\t')
			newt = extract_cmd(str, newt, &i);
		else
			i++;
	}
	return (newt);
}

char	**split_quotes(char *str, char **newt, int *i)
{
	char	quote;
	int		j;
	int		k;
	int		size;
	char	**tmp;

	j = 0;
	k = -1;
	size = *i;
	quote = check_expansions(str[*i]);
	tmp = ft_realloc2(newt);
	while (tmp && tmp[j])
		j++;
	while (str[size] == quote)
		size++;
	while (str[size] && str[size] != quote)
		size++;
	tmp[j] = ft_strnew(size - *i);
	while (++(*i) < size)
		tmp[j][++k] = str[*i];
	while (str[*i] == quote)
		(*i)++;
	return (tmp);
}

char	**extract_cmd(char *str, char **newt, int *i)
{
	int		j;
	int		k;
	int		size;
	char	**tmp;

	j = 0;
	k = 0;
	size = *i;
	tmp = ft_realloc2(newt);
	while (tmp && tmp[j] != 0)
		j++;
	while (str[size] && str[size] != ' ' && str[size] != '\t')
		size++;
	tmp[j] = ft_strnew(size - *i);
	while (*i < size)
	{
		tmp[j][k] = str[*i];
		k++;
		(*i)++;
	}
	newt ? free(newt) : 0;
	return (tmp);
}

char	check_expansions(char exp)
{
	if (exp == 40)
		exp = 41;
	else if (exp == 91)
		exp = 93;
	return (exp);
}
