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
		if (shell->lineinfo->spot_hist < (int)shell->history->size - 1)
		{
			LINE;
			CLEAR_LN;
			print_interp();
			shell->lineinfo->spot_hist++;
			ft_putstr(vectspot(shell->lineinfo->spot_hist, shell->history));
			return (ft_strdup(vectspot(shell->lineinfo->spot_hist, shell->history)));
		}
	}
	else if (str1[2] == 'B') 	//down
	{
			if (shell->lineinfo->spot_hist > -1)
			{
				LINE;
				CLEAR_LN;
				print_interp();
				ft_putstr(vectspot(shell->lineinfo->spot_hist, shell->history));
				shell->lineinfo->spot_hist--;
				if (shell->lineinfo->spot_hist > -1)
					return ft_strdup((vectspot(shell->lineinfo->spot_hist + 1, shell->history)));
			}
			if (shell->lineinfo->spot_hist == -1)
			{
				LINE;
				CLEAR_LN;
				print_interp();
			}
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
	termresetline(shell);
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
	if (ft_strcmp("", ret) && shell->lineinfo->spot_hist == -1 && ft_strcmp(vectspot(0, shell->history), ret) != 0)
		vect_insert(shell->history, 0, ft_strdup(ret));
	insert_char("\n");
	col_vect(vect);
	ret[bytes_read - 1] = '\0';
	return (ret);
}
