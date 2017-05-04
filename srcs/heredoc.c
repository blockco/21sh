#include "../headers/minishell.h"

void print_help(int fd, char *ret)
{
	write(fd, ret, ft_strlen(ret));
	write(fd, "\n", 1);
}

char *here_help(char *stopper, char *ret, int *going, int fd)
{
	ft_putendl("");
	if (ft_strcmp(ret, stopper) == 0)
		*going = 0;
	else
		print_help(fd, ret);
	free (ret);
	return (ft_strnew(0));
}

void	*read_tmp_here(t_shell *shell, char *stopper, int fd)
{
	char		*str1;
	char		*ret;
	int 		going;

	going = 1;
	ret = ft_strnew(0);
	str1 = ft_strnew(BUFF_SIZE);
	termresetline(shell);
	while (going)
	{
		bzero(str1, BUFF_SIZE);
		read(0, str1, BUFF_SIZE);
		if (check_char(str1, shell) || (shell->lineinfo->dq && str1[0] == 13))
		{
			INSERT_MODE_ON;
			ft_putstr(str1);
			INSERT_MODE_OFF;
			ret = addtobuff(shell, ret, str1);
			shell->lineinfo->size++;
		}
		if (str1[0] == 13)
			ret = here_help(stopper, ret, &going, fd);
	}
	return (ret);
}
