#include "../headers/minishell.h"

// char **alloc

char **check_file_agg(char **temp)
{
	int i;
	char **ret;
	int a;

	i = 0;
	a = 0;
	ret = malloc(sizeof(char*));
	while (temp[i])
	{
		if (!is_file_agg(temp[i]))
		{
			a++;
			ret = (char**)realloc(ret, ((sizeof(char*)) * (a + 1)));
			ret[a - 1] = ft_strdup(temp[i]);
		}
		i++;
	}
	ret[a] = NULL;
	freedub(temp);
	return ret;
}

int fileagghelp(char **split, int dir)
{
	if (ft_strcmp(split[1], "-") == 0 && is_all_num(split[0]) && dir == 1)
	{
		close (ft_atoi(split[0]));
		freedub(split);
		return 1;
	}
	else if (ft_strcmp(split[0], "-") == 0 && is_all_num(split[1]) && dir == 0)
	{
		close (ft_atoi(split[1]));
		freedub(split);
		return 1;
	}
	else if (is_all_num(split[0]) && is_all_num(split[1]) && dir == 0)
	{
		dup2(ft_atoi(split[1]), ft_atoi(split[0]));
		freedub(split);
		return 1;
	}
	else if (is_all_num(split[0]) && is_all_num(split[1]) && dir == 1)
	{
		dup2(ft_atoi(split[0]), ft_atoi(split[1]));
		freedub(split);
		return 1;
	}
	return 0;
}

int is_file_agg(char *str)
{
	char **split;
	int dir;
	int num1;
	int num2;

	num1 = 0;
	num2 = 0;
	split = NULL;
	if (ft_strchr(str, '&') && (ft_strchr(str, '>') || ft_strchr(str, '<')))
		split = ft_strsplit(str, '&');
	else
		return 0;
	dir  = 0;
	if (split && split[0] && split[1] && !split[2])
	{
		if (split[0][(int)ft_strlen(split[0]) - 1] == '>')
			dir = 0;
		else if (split[0][(int)ft_strlen(split[0]) - 1] == '<')
			dir = 1;
		else
		{
			freedub(split);
			return 0;
		}
		split[0][(int)ft_strlen(split[0]) - 1] = '\0';
		return(fileagghelp(split, dir));
		// if (ft_strcmp(split[1], "-") == 0 && is_all_num(split[0]) && dir == 1)
		// {
		// 	close (ft_atoi(split[0]));
		// 	freedub(split);
		// 	return 1;
		// }
		// else if (ft_strcmp(split[0], "-") == 0 && is_all_num(split[1]) && dir == 0)
		// {
		// 	close (ft_atoi(split[1]));
		// 	freedub(split);
		// 	return 1;
		// }
		// else if (is_all_num(split[0]) && is_all_num(split[1]) && dir == 0)
		// {
		// 	dup2(ft_atoi(split[1]), ft_atoi(split[0]));
		// 	freedub(split);
		// 	return 1;
		// }
		// else if (is_all_num(split[0]) && is_all_num(split[1]) && dir == 1)
		// {
		// 	dup2(ft_atoi(split[0]), ft_atoi(split[1]));
		// 	freedub(split);
		// 	return 1;
		// }
	}
	return 0;
}
