/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.us>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 23:40:17 by rpassafa          #+#    #+#             */
/*   Updated: 2017/02/15 23:41:17 by rpassafa         ###   ########.us       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	printfirstpath(char *cwd)
{
	int i;
	char *tmp;

	i = ft_strlen(cwd);
	i--;
	while (cwd[i] != '/')
		i--;
	i++;
	while (cwd[i])
	{
		tmp = ft_strnew(2);
		tmp[0] = cwd[i++];
		insert_char(tmp);
		free (tmp);
		// ft_putchar(cwd[i++]);
	}
}

void	print_interp(void)
{
	char	*cwd;
	char	buff[PATH_MAX + 1];
	LEFT_LN;

	cwd = getcwd(buff, PATH_MAX + 1);
	insert_str("[");
	printfirstpath(cwd);
	insert_str("]");
	// ft_putstr(" ༼ つ ͠° ͟ ͟ʖ ͡° ༽つ > ");
}
