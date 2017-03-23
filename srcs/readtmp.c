/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readtmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.us>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 00:26:40 by rpassafa          #+#    #+#             */
/*   Updated: 2017/02/16 00:26:49 by rpassafa         ###   ########.us       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void checkarrowkeys(char *str1, t_shell *shell)
{
	if (str1[2] == 'C')
	{
		;
	}
	else if (str1[2] == 'A')
	{
		;
	}
	else if (str1[2] == 'B')
	{
		;
	}
	else if (str1[2] == 'D')
	{
		;
	}
	shell->lineinfo->left = 0;
}

char	*read_tmp(t_shell *shell)
{
	char		*str1;
	int			bytes_read;
	char		*ret;
	t_vector	*vect;

	vect = vect_new(10, sizeof(char*));
	str1 = ft_strnew(BUFF_SIZE);
	ret = ft_strnew(1);
	bytes_read = 0;
	while (ft_strchr(ret, '\n') == NULL)
	{
		vect_insert(vect, vect->size, &str1);
		str1 = ft_strnew(BUFF_SIZE);
		if (bytes_read > 0)
			vect_insert(vect, vect->size, &ret);
		bytes_read += read(0, str1, BUFF_SIZE);
		if (check_char(str1))
		{
			if (bytes_read > 1)
				ret = ft_strjoin(ret, (const char*)str1);
			else
			{
				ret = ft_strdup(str1);
			}
			ft_putstr(str1);//whats printing to screen
		}
		// else if (str1[2] == 'C')
		// {
		// 	insert_str(str1);
		// 	ret = ft_strjoin(ret, "");
		// }
		// else if (str1[2] == 'A')
		// {
		// 	CLEAR;
		// 	insert_str(vectspot(0, shell->history));
		// 	ret = ft_strjoin(ret, "");
		// }
		else
		{
			checkarrowkeys(str1, shell);
			ret = ft_strjoin(ret, "");
		}
		if (str1[0] == 13)
			break;
	}
	// INSERT_MODE_ON;
	// CLEAR;
	// INSERT_MODE_OFF;
	// LINE;
	vect_insert(shell->history, shell->history->size, ft_strdup(ret));
	insert_char("\n");
	col_vect(vect);
	ret[bytes_read - 1] = '\0';
	return (ret);
}
