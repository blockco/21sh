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
	while (temp[i] && !isredir(temp[i]))
		i++;
	return i;
}

int getredir(char *str)
{
	if (!str)
		return 0;
	if (ft_strcmp(str, "|") == 0)
		return 1;
	if (ft_strcmp(str, ">") == 0)
		return 2;
	if (ft_strcmp(str, ">>") == 0)
		return 3;
	if (ft_strcmp(str, "<") == 0)
		return 4;
	if (ft_strcmp(str, "<<") == 0)
		return 5;
	return 0;
}

void checkthisvect(t_vector *cmd_vect)
{
	size_t i;
	t_command *test;

	i = 0;
	while (i < cmd_vect->size)
	{
		test = vectspot(i, cmd_vect);
		i++;
		int a = 0;
		while (test->args[a])
			ft_putendl(test->args[a++]);
		ft_putnbr(test->redirect);
		ft_putendl("");
	}
}

void printlinkedcmds(t_command *head)
{
	t_command *cur;
	cur = head;
	while (cur)
	{
		int i = 0;
		while (cur->args[i])
			ft_putendl(cur->args[i++]);
		ft_putnbr(cur->redirect);
		ft_putendl("");
		if(cur->file)
			ft_putendl(cur->file);
		cur = cur->next;
	}
}

void free_cmd_list(t_command *head)
{
	t_command *cur;
	t_command *prev;
	int i;

	cur = head;
	while (cur)
	{
		i = 0;
		prev = cur;
		cur = cur->next;
		free (prev);
		prev = NULL;
	}
}

void createcmds(t_command *head, char **temp)
{
	int i;
	t_command *new;
	t_command *next;

	new = head;
	while (temp[0])
	{
		i = 0;
		new->args = malloc(sizeof(char*) * findargs(temp) + 1);
		while (temp[i] && !isredir(temp[i]))
		{
			new->args[i] = ft_strdup(temp[i]);
			i++;
		}
		new->args[i] = NULL;
		if (temp[i] && isredir(temp[i]))
		{
			new->redirect = getredir(temp[i]);
			i++;
		}
		else
			new->redirect = 0;
		if (temp[i] && new->redirect > 1 && new->redirect < 6)
		{
			new->file = ft_strdup(temp[i]);
			i++;
		}
		else
			new->file = NULL;
		temp += i;
		if (temp[0])
		{
			next = malloc(sizeof(t_command));
			new->next = next;
			new = new->next;
		}
		else
			new->next = NULL;
	}
	temp -=  i;
	printlinkedcmds(head);
	// free_cmd_list(head);
}
