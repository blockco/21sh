#include "../headers/minishell.h"

int check_char(char *data, t_shell *shell)
{
	if (data[0] == '"' && !shell->lineinfo->dq)
	{
		shell->lineinfo->dq = 1;
		return 1;
	}
	else if (data[0] == '"' && shell->lineinfo->dq)
	{
		shell->lineinfo->dq = 0;
		return 1;
	}
	if (data[0] > 31 && data[0] < 127)
		return 1;
	if (data[0] == 13 && shell->lineinfo->dq)
		return (1);
	return 0;
}
