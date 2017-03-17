/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.us>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 13:13:39 by rpassafa          #+#    #+#             */
/*   Updated: 2017/02/20 17:59:58 by rpassafa         ###   ########.us       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../libft/libft.h"
#include "../headers/vector.h"

void	nonrun(char **temp)
{
	// ft_putstr("unknown command rsh: ");
	// ft_putendl(temp[0]);
	insert_str("unknown command rsh: ");
	insert_str(temp[0]);
	insert_char("\n");
	freedub(temp);
}

void	dofree(char **temp)
{
	temp++;
	freedub(temp);
}

void	handlearg(int argc, char **argv)
{
	if (argc < 0)
		;
	if (argv)
		;
}

void	logicrun(int ret, char **temp, t_vector *vect)
{
	if (ret == 1 || ret == -1)
		freedub(temp);
	else if (!checklocsp(temp[0], temp, vect))
	{
		if (findenvvarint(vect, "PATH") == -1 ||
		(temp[0] && !execprog(temp[0], getbins(vect), temp, vect)))
			nonrun(temp);
	}
	else
		dofree(temp);
}


int			setup_term(t_shell *shell)
{
	struct termios	new;

	if (tcgetattr(0, &shell->old) < 0)
		return (-1);
	new = shell->old;
	new.c_lflag &= ~(ECHO | ICANON);
	// new.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

	new.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
	| INLCR | IGNCR | ICRNL | IXON);
	new.c_cflag &= ~(CSIZE | PARENB);
	new.c_cflag |= CS8;
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSAFLUSH, &new) < 0)
		return (-1);
	shell->now = &new;
	return (1);
}

int shellexit(t_shell *shell)
{
	if (tcsetattr(0, TCSAFLUSH, &shell->old) < 0)
		return (-1);
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	char		*str;
	t_vector	*vect;
	t_shell		*shell;
	char		**temp;
	int			ret;

	shell = malloc(sizeof(t_shell));
	setup_term(shell);
	handlearg(argc, argv);
	vect = vect_new(32, sizeof(char*));
	storeenv(vect, envp);
	while (1)
	{
		print_interp();
		str = read_tmp(shell);
		temp = parseinput(str);
		checkenv(temp, vect);
		ret = runbuilt(temp, vect);
		logicrun(ret, temp, vect);
		if (ret == -1)
			break ;
	}
	shellexit(shell);
	exit(0);
	return (0);
}
