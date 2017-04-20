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

void printlinkedcmds(t_command *head)
{
	t_command *cur;
	t_file		*h_file;
	cur = head;
	while (cur)
	{
		h_file = cur->head_file;
		int i = 0;
		while (cur->args[i])
			ft_putendl(cur->args[i++]);
		ft_putnbr(cur->pipe);
		ft_putchar('\n');
		while (h_file)
		{
			ft_putendl("in redirect files");
			if (h_file->file)
				ft_putendl(h_file->file);
			h_file = h_file->next;
		}
		cur = cur->next;
	}
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
		//seperate function
		if (getredir(temp[i]) == 1)
		{
			new->pipe = 1;
			i++;
		}
		else
			new->pipe = 0;
		new->head_file = NULL;
		if (temp[i] && !new->pipe)
		{
			new->head_file = (t_file*)malloc(sizeof(t_file));
			file_point = new->head_file;
			while (temp[i] && !new->pipe)
			{
				file_point->redir = getredir(temp[i]);
				file_point->file = NULL;
				i++;
				if (temp[i])
				{
					file_point->file = ft_strdup(temp[i]);
					i++;
				}
				while (temp[i] && !isredir(temp[i]))
				{
					ft_putendl("extra");
					ft_putendl(temp[i]);
					i++;
				}
				if (temp[i] && getredir(temp[i]) == 1)
				{
					new->pipe = 1;
					i++;
				}
				else if (!temp[i])
					new->pipe = 0;
				else
				{
					file_point->next = (t_file*)malloc(sizeof(t_file));
					file_point = file_point->next;
				}
				file_point->next = NULL;
			}
		}
		if (temp[i])
		{
			new->next = malloc(sizeof(t_command));
			new = new->next;
		}
		new->next = NULL;
		a += i;
		temp += i;
	}
	temp -=  a;
	printlinkedcmds(head);
	// free_cmd_list(head);
}
