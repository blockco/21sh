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

void printlinkedcmds(t_command *head)
{
	t_command *cur;
	cur = head;
	while (cur)
	{
		int i = 0;
		while (cur->args[i])
			ft_putendl(cur->args[i++]);
		cur = cur->next;
	}
	ft_putendl("here");
}

void createcmds(t_command *head, char **temp)
{
	int i;
	int a;
	t_command 	*new;
	t_file		*file_point;

	a = 0;
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
		new->head_file = NULL;
		if (temp[i] && getredir(temp[i]) > 1 && getredir(temp[i]) < 6)
		{
			file_point = new->head_file;
			while (temp[i])
			{
				file_point = malloc(sizeof(t_file));
				file_point->redir = getredir(temp[i]);
				file_point->file = NULL;
				i++;
				if (temp[i])
					file_point->file = ft_strdup(temp[i]);
				file_point->parent = new;
				while (temp[i] && !isredir(temp[i]))
				{
					//extra args
					i++;
				}
				if (temp[i] && getredir(temp[i]) == 1)
				{
					file_point->parent->pipe = 1;
					i++;
					file_point->next = NULL;
					break;
				}
				else if (!temp[i])
				{
					file_point->parent->pipe = 0;
					file_point->next = NULL;
					break;
				}
				file_point->next = (t_file*)malloc(sizeof(t_file));
				file_point = file_point->next;
				file_point->next = NULL;
			}
		}
		else if (getredir(temp[i]) == 1)
		{
			i++;
			new->pipe = 1;
		}
		else
			new->pipe = 0;
		if (temp[i])
		{
			new->next = malloc(sizeof(t_command));
			new = new->next;
		}
		new->next = NULL;
		a += i;
		temp += i;
	}
	new = NULL;
	temp -=  a;
	// printlinkedcmds(head);
	// free_cmd_list(head);
}
