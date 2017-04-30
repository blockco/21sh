#include "../headers/minishell.h"

int check_char(char *data, t_shell *shell)
{
	if ((data[0] == '"' || data[0] == 39 || data[0] == 40) && !shell->lineinfo->dq)
	{
		shell->lineinfo->dq = 1;
		if (data[0] == 40)
			shell->lineinfo->dqbuff = 41;
		else
			shell->lineinfo->dqbuff = data[0];
		return 1;
	}
	else if (data[0] == shell->lineinfo->dqbuff && shell->lineinfo->dq)
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
