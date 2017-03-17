#include "../headers/minishell.h"

int check_char(char *data)
{
	if (data[0] > 32 && data[0] < 127)
		return 1;
	// else if (K_UP == (int)data[0])
	// 	return 1;
	// ft_putstr(data);
	return 0;
}
