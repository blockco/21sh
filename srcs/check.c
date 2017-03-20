#include "../headers/minishell.h"

int check_char(char *data)
{
	if (data[0] > 31 && data[0] < 127)
		return 1;
	// else if (ft_strcmp(data, K_UP))
	// 	return 1;
	// ft_putstr(data);
	return 0;
}
