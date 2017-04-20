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
	ft_putstr("unknown command rsh: ");
	ft_putendl(temp[0]);
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
		return;
		// freedub(temp);
	else if (!checklocsp(temp[0], temp, vect))
	{
		if (findenvvarint(vect, "PATH") == -1 ||
		(temp[0] && !execprog(temp[0], getbins(vect), temp, vect)))
			nonrun(temp);
	}
	// else
	// 	dofree(temp);
}

int shellexit(t_shell *shell)
{
	if (tcsetattr(0, TCSAFLUSH, &shell->old) < 0)
		return (-1);
	KEYS_OFF;
	return (0);
}

int		main(int argc, char **argv, char **envp)
{
	char		*str;
	t_vector	*vect;
	t_command	*head;
	t_command	*curr;
	t_shell		*shell;
	char		**temp;
	char 		*use;
	char		**cmds;
	int			ret;
	int 		i;

	i = 0;
	shell = malloc(sizeof(t_shell));
	setup_term(shell);
	handlearg(argc, argv);
	vect = vect_new(32, sizeof(char*));
	storeenv(vect, envp);
	head = malloc(sizeof(t_command));
	while (1)
	{
		print_interp();
		str = read_tmp(shell);
		cmds = ft_strsplit(str, ';');
		i = 0;
		while (cmds[i])
		{
			use = ft_strtrim(cmds[i]);
			temp = parseinput(use);
			checkenv(temp, vect);
			createcmds(head, temp);
			curr = head;
			while (curr)
			{
				ret = runbuilt(curr->args, vect);
				logicrun(ret, curr->args, vect);
				curr = curr->next;
			}
			// free(use);
			i++;
			if (ret == -1)
				break ;
			// freedub(temp);
		}
		// freedub(cmds);
		if (ret == -1)
			break ;
	}
	shellexit(shell);
	exit(0);
	return (0);
}
