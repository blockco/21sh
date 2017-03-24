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

char *checkarrowkeys(char *str1, t_shell *shell, char *ret)
{
	if (str1[2] == 'C') 		//right
	{
		if (shell->lineinfo->left > 0)
		{
			shell->lineinfo->left--;
			shell->lineinfo->right++;
			RIGHT;
		}
	}
	else if (str1[2] == 'A') 	//up
	{
		LINE;
		CLEAR_LN;
		print_interp();
		return(ft_strdup(""));
	}
	else if (str1[2] == 'B') 	//down
	{
		LINE;
		CLEAR_LN;
		print_interp();
		return(ft_strdup(""));
	}
	else if (str1[2] == 'D')	//left
	{
		if (shell->lineinfo->size > shell->lineinfo->left)
		{
			LEFT;
			shell->lineinfo->left++;
		}
	}
	else if (str1[0] == 127)
	{
		if (shell->lineinfo->size > 0 && shell->lineinfo->left < shell->lineinfo->size)
		{
			shell->lineinfo->size--;
			LEFT;
			DEL_CHAR;
		}
	}
	return(ft_strjoin(ret, ""));
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
	shell->lineinfo->size = 0;
	shell->lineinfo->left = 0;
	shell->lineinfo->right = 0;
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
				ret = ft_strdup(str1);
			INSERT_MODE_ON;
			ft_putstr(str1);
			INSERT_MODE_OFF;
			shell->lineinfo->size++;
		}
		else
			ret = checkarrowkeys(str1, shell, ret);
		if (str1[0] == 13)
			break;
	}
	vect_insert(shell->history, shell->history->size, ft_strdup(ret));
	insert_char("\n");
	col_vect(vect);
	ret[bytes_read - 1] = '\0';
	return (ret);
}
