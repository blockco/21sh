#include "../headers/minishell.h"

void	insert_str(char *cwd)
{
	int i;
	char *tmp;

	i = 0;
	INSERT_MODE_ON;
	while (cwd[i])
	{
		tmp = ft_strnew(2);
		tmp[0] = cwd[i++];
		insert_char(tmp);
		free (tmp);
		// ft_putchar(cwd[i++]);
	}
	INSERT_MODE_OFF;
}

void	insert_char(char *c)
{
	INSERT_MODE_ON;
	tputs(c, 1, ft_putchar);
	INSERT_MODE_OFF;
}
