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

int count_args(t_command *head)
{
	t_command *cur;
 	t_file		*h_file;
	int i;
	int z;

 	cur = head;
	h_file = cur->head_file;
	i = 0;
	while (cur->args[i])
		i++;
 	while (h_file)
 	{
		z = 0;
		while(h_file->extra[z++])
			i++;
		h_file = h_file->next;
 	}
	return i;
}

void c_args(t_command *head)
{
	t_command 	*cur;
	t_file		*h_file;
	char 		**temp;
	int 		i;
	int			a;

	cur = head;
	while (cur)
	{
		h_file = cur->head_file;
		temp = (char**)malloc(sizeof(char*) * (count_args(cur) + 1));
		i = 0;
		while(cur->args[i])
		{
			temp[i] = ft_strdup(cur->args[i]);
			i++;
		}
		while (h_file)
		{
			a = 0;
			while(h_file->extra[a])
			{
				temp[i] = ft_strdup(h_file->extra[a]);
				a++;
				i++;
			}
			h_file = h_file->next;
		}
		freedub(cur->args);
		temp[i] = NULL;
		cur->args =	temp;
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
		if (getredir(temp[i]) == 1)
		{
			new->pipeout = 1;
			i++;
		}
		else
			new->pipeout = 0;
		new->head_file = NULL;
		if (temp[i] && !new->pipeout)
		{
			new->head_file = (t_file*)malloc(sizeof(t_file));
			file_point = new->head_file;
			while (temp[i] && !new->pipeout)
			{
				file_point->redir = getredir(temp[i]);
				file_point->file = NULL;
				i++;
				if (temp[i])
				{
					file_point->file = ft_strdup(temp[i]);
					i++;
				}
				file_point->extra = malloc(sizeof(char*) * findargs(temp) + 1);
				int b = 0;
				while (temp[i] && !isredir(temp[i]))
				{
					file_point->extra[b] = ft_strdup(temp[i]);
					i++;
					b++;
				}
				file_point->extra[b] = NULL;
				if (temp[i] && getredir(temp[i]) == 1)
				{
					new->pipeout = 1;
					i++;
				}
				else if (!temp[i])
					new->pipeout = 0;
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
			if (new->pipeout)
				new->next->pipein = 1;
			new = new->next;
		}
		new->next = NULL;
		a += i;
		temp += i;
	}
	temp -=  a;
	c_args(head);
}
