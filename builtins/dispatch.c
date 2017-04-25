/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.us>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 23:34:34 by rpassafa          #+#    #+#             */
/*   Updated: 2017/02/15 23:34:37 by rpassafa         ###   ########.us       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	extendrun(t_command *curr, t_vector *vect)
{
	if (curr->args[0] && ft_strcmp(curr->args[0], "setenv") == 0)
	{
		if (curr->args[1])
			setenv_b(curr->args[1], curr->args[2], vect);
		return (1);
	}
	if (curr->args[0] && ft_strcmp(curr->args[0], "unsetenv") == 0)
	{
		if (curr->args[1])
			unsetenv_b(curr->args[1], vect);
		return (1);
	}
	if (curr->args[0] && ft_strcmp(curr->args[0], "echo") == 0)
	{
		if (curr->args[1])
			echo_b(curr->args);
		return (1);
	}
	if (curr->args[0] && (ft_strcmp(curr->args[0], "exit") == 0
	|| ft_strcmp(curr->args[0], "EXIT") == 0))
		return (-1);
	return (0);
}

int	runbuilt(t_command *curr, t_vector *vect)
{
	if (curr->args[0] && ft_strcmp(curr->args[0], "env") == 0)
	{
		getenv_b(vect);
		return (1);
	}
	if (curr->args[0] && ft_strcmp(curr->args[0], "cd") == 0)
	{
		if (curr->args[1] == NULL)
			changedirs(NULL, vect);
		else if (curr->args[1] && curr->args[1] == NULL)
			changedirs(curr->args[1], vect);
		else
			ft_putendl("to many arguments in cd");
		return (1);
	}
	return (extendrun(curr, vect));
}
