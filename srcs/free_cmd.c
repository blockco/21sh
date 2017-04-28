#include "../headers/minishell.h"

void free_file_list(t_file *head)
{
	t_file *cur;
	t_file *prev;

	cur = head;
	while (cur)
	{
		free(cur->file);
		freedub(cur->extra);
		prev = cur;
		cur = cur->next;
		free(prev);
		prev = NULL;
	}
}

void free_cmd_list(t_command *head)
{
	t_command *cur;
	t_command *prev;

	cur = head;
	while (cur)
	{
		if (cur->head_file)
			free_file_list(cur->head_file);
		freedub(cur->args);
		prev = cur;
		cur = cur->next;
		free(prev);
		prev = NULL;
	}
}
