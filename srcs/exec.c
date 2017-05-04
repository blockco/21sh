/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.us>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 00:07:51 by rpassafa          #+#    #+#             */
/*   Updated: 2017/02/20 18:00:30 by rpassafa         ###   ########.us       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void run_child_build(t_command *curr, t_exec test, int nice, t_vector *vect)
{
	signal(SIGINT, SIG_DFL);
	if (curr->next)
	{
		dup2(test.fd[1],1);
		close(test.fd[0]);
	}
	dup2(nice, 0);
	if (ft_strequ(curr->args[0], "echo"))
	{
		test.err = echo_b(curr->args);
		exit(0);
	}
	else if (ft_strequ(curr->args[0], "env"))
	{
		getenv_b(vect);
		exit(0);
	}
	else
		test.err = execve(curr->args[0], curr->args, test.env);
}

void	runprog(t_command *curr, t_vector *vect)
{
	t_exec test;
	static int nice = 0;

	test.env = cpenv_b(vect);

	if (curr->next)
		pipe(test.fd);
	test.pid = fork();
	if (test.pid == 0)
		run_child_build(curr, test, nice, vect);
	else if (test.pid < 0)
	{
		ft_putstr("fork failed with error code ");
		ft_putnbr(test.pid);
		ft_putchar('\n');
		exit(-1);
	}
	wait(&test.status);
	close(test.fd[1]);
	nice = test.fd[0];
}

int		checkloc(t_command *curr, int size, t_vector *vect)
{
	struct stat sb;

	if (lstat(curr->args[0], &sb) == -1)
	{
		return (size);
	}
	else
		runprog(curr, vect);
	return (-1);
}

int		checklocsp(t_command *curr, t_vector *vect)
{
	struct stat sb;

	if (lstat(curr->args[0], &sb) == -1)
	{
		return (0);
	}
	else
	{
		runprog(curr, vect);
		return (1);
	}
}

int		execprog(t_command *curr, char **bins, t_vector *vect)
{
	int		size;
	char	*test;

	size = countarray(bins);
	size--;
	size = checkloc(curr, size, vect);
	if (size == -1)
		return (1);
	while (size > -1)
	{
		test = checkbin(curr->args[0], bins[size]);
		if (test != NULL)
		{
			freedub(bins);
			free(curr->args[0]);
			curr->args[0] = test;
			runprog(curr, vect);
			return (1);
		}
		else
			size--;
	}
	freedub(bins);
	return (0);
}

//redirection
int		check_cmd_helper(char *test, int size)
{
	struct stat sb;

	if (lstat(test, &sb) == -1)
	{
		return (size);
	}
	return (-1);
}

int		checkcmd(char *str, char **bins)
{
	int		size;
	char	*test;

	size = countarray(bins);
	size--;
	size = check_cmd_helper(str, size);
	if (size == -1)
		return (1);
	while (size > -1)
	{
		test = checkbin(str, bins[size]);
		if (test != NULL)
		{
			freedub(bins);
			free(test);
			return (1);
		}
		else
			size--;
	}
	freedub(bins);
	return (0);
}
