#include "../headers/minishell.h"

int isredir(char *str)
{
	if (ft_strcmp(str, "|") == 0 || ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0)
		return 1;
	return 0;
}

int findargs(char **temp)
{
	int i;

	i = 0;
	while (temp[i])
	{
		if (isredir(temp[i]))
			return i++;
	}
	return i;
}

int getredir(char *str)
{
	if (ft_strcmp(str, "|"))
		return 1;
	if (ft_strcmp(str, ">"))
		return 2;
	if (ft_strcmp(str, ">>"))
		return 3;
	if (ft_strcmp(str, "<"))
		return 4;
	if (ft_strcmp(str, "<<"))
		return 5;
	return 0;
}

void createcmds(t_vector *cmd_vect, char **temp)
{
	cmd_vect = NULL;
	if (temp)
		;
	// t_command *new;
	//
	// new = malloc(sizeof(t_command));
	// while (temp[i])
	// {
	// 	save = findargs(temp);
	// 	new->args = (char**)malloc(sizeof(char*) * findargs(temp));
	// 	a = 0;
	// }
}
