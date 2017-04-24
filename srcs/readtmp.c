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
	shell->lineinfo->size = ft_strlen(ret);
	if (str1[2] == 'C') 		//right
	{
		if (shell->lineinfo->linespot > 0)
		{
			shell->lineinfo->linespot--;
			RIGHT;
		}
	}
	else if (str1[2] == 'D')	//left
	{
		if (shell->lineinfo->size > shell->lineinfo->linespot)
		{
			LEFT;
			shell->lineinfo->linespot++;
		}
	}
	else if (str1[2] == 'A') 	//up
	{
		LINE;
		CLEAR_LN;
		print_interp();
		if (shell->lineinfo->spot_hist < (int)shell->history->size - 1)
		{
			shell->lineinfo->spot_hist++;
			shell->lineinfo->linespot = 0;
			ft_putstr(*(char **)vectspot(shell->lineinfo->spot_hist, shell->history));
			return(ft_strdup(*(char **)vectspot(shell->lineinfo->spot_hist, shell->history)));
		}
		else
		{
			shell->lineinfo->linespot = 0;
			ft_putstr(*(char **)vectspot(shell->lineinfo->spot_hist, shell->history));
			return(ft_strdup(*(char **)vectspot(shell->lineinfo->spot_hist, shell->history)));
		}
	}
	else if (str1[2] == 'B')	//down
	{
		LINE;
		CLEAR_LN;
		print_interp();
		if (shell->lineinfo->spot_hist > -1)
		{
			shell->lineinfo->spot_hist--;
			if (shell->lineinfo->spot_hist > -1)
			{
				shell->lineinfo->linespot = 0;
				ft_putstr(*(char **)vectspot(shell->lineinfo->spot_hist, shell->history));
				return(ft_strdup(*(char **)vectspot(shell->lineinfo->spot_hist, shell->history)));
			}
			else if (shell->lineinfo->spot_hist == -1)
			{
				shell->lineinfo->linespot = 0;
				ft_putstr("");
				return(ft_strdup(""));
			}
		}
	}
	else if (str1[0] == 127)
	{
		if (shell->lineinfo->linespot < (int)ft_strlen(ret))
		{
			//fix del function
			;
			// shell->lineinfo->size--;
			// LEFT;
			// DEL_CHAR;
			// del_fun(ret, shell->lineinfo->linespot);
		}
	}
	return(ft_strjoin(ret, ""));
}



char	*read_tmp(t_shell *shell)
{
	char		*str1;
	char		*ret;
	char		*tmp;

	ret = ft_strnew(0);
	str1 = ft_strnew(BUFF_SIZE);
	termresetline(shell);
	while (1)
	{
		// str1 = ft_strnew(BUFF_SIZE);
		bzero(str1, BUFF_SIZE);
		read(0, str1, BUFF_SIZE);
		if (str1[0] == 13 && !shell->lineinfo->dq)
		{
			free(str1);
			break;
		}
		if (check_char(str1, shell) || (shell->lineinfo->dq && str1[0] == 13))
		{
			INSERT_MODE_ON;
			ft_putstr(str1);
			INSERT_MODE_OFF;
			ret = join_free_front(ret, str1);
			//  ret = addtobuff(shell, ret, str1);
			shell->lineinfo->size++;
		}
		else
			ret = checkarrowkeys(str1, shell, ret);
		// else
		// 	free(str1);
	}
	ft_putchar('\n');
	if (ft_strcmp("", ret) && shell->lineinfo->spot_hist == -1 && ft_strcmp(vectspot(0, shell->history), ret) != 0)
	{
		tmp = ft_strdup(ret);
		vect_insert(shell->history, 0, &tmp);
	}
	// while (shell->endl)
	// {
	// 	shell->endl--;
	// 	insert_char("\n");
	// }
	// col_vect(vect);
	//history not freed
	return (ret);
}
