#include "../headers/minishell.h"

int is_all_num(char *str)
{
	int i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (!str[i])
		return 1;
	return 0;

}
