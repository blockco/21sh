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


//debug scriptt
void printlinkedcmds(t_command *head)
{
	t_command 	*cur;
	t_file		*h_file;
	cur = head;

	while (cur)
	{
		ft_putendl("");
		ft_putendl("IS A CMD");
		h_file = cur->head_file;
		int i = 0;
		ft_putnbr(cur->pipein);
		ft_putendl(" = pipeIN");
		ft_putnbr(cur->pipeout);
		ft_putendl(" = pipeOUT");
		while (cur->args[i])
			ft_putendl(cur->args[i++]);
		while (h_file)
		{
			ft_putendl("in redirect files");
			if (h_file->file)
				ft_putendl(h_file->file);
			h_file = h_file->next;
		}
		ft_putendl("IS A CMD");
		ft_putendl("");
		cur = cur->next;
	}
}
//debug scriptt

void	nonrun(char **temp)
{
	INSERT_MODE_ON;
	ft_putstr("unknown command rsh: ");
	ft_putendl(temp[0]);
	INSERT_MODE_OFF;
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

void	logicrun(int ret, t_command *curr, t_vector *vect)
{
	if (ret == 1 || ret == -1)
		return;
		// freedub(temp);
	else if (!checklocsp(curr, vect))
	{
		if (findenvvarint(vect, "PATH") == -1 ||
		(curr->args[0] && !execprog(curr, getbins(vect), vect)))
			nonrun(curr->args);
	}
	// else
	// 	dofree(temp);
}

int shellexit(t_shell *shell)
{
	if (tcsetattr(0, TCSAFLUSH, &shell->old) < 0)
		return (-1);
	KEYS_OFF;
	exit(0);
	return (0);
}


//REDIRECT
int openfile(t_file *file)
{
	if (file->redir == 2)
		return(open(file->file, O_WRONLY | O_TRUNC | O_CREAT, 0600));
	if (file->redir == 3)
		return(open(file->file, O_WRONLY | O_APPEND | O_CREAT, 0600));
	if (file->redir == 4)
		return(open(file->file, O_RDONLY));
	if (file->redir == 5)
		return(open("/tmp/heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0600));
	ft_putendl("did not open!!!");
	return -1;
}

int loopredir(t_command *curr, t_vector *vect, t_shell *shell)
{
	int ret;
	int fd;
	t_file *h_file;

	h_file = curr->head_file;
	while (h_file && checkcmd(curr->args[0], getbins(vect)))
	{
		fd = openfile(h_file);
		if (h_file->redir == 2 || h_file->redir == 3)
			dup2(fd, 1);
		if (h_file->redir == 4)
			dup2(fd, 0);
		if (h_file->redir == 5)
		{
			read_tmp_here(shell, h_file->file, fd);
			close(fd);
			fd = open("/tmp/heredoc", O_RDONLY);
			dup2(fd, 0);
		}
		close(fd);
		h_file = h_file->next;
	}
	ret = runbuilt(curr, vect);
	logicrun(ret, curr, vect);
	return (ret);
}

//REDIRECT
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
	signal(SIGINT, SIG_IGN);
	shell = malloc(sizeof(t_shell));
	setup_term(shell);
	handlearg(argc, argv);
	vect = vect_new(32, sizeof(char*));
	storeenv(vect, envp);
	while (1)
	{
		print_interp();
		str = read_tmp(shell);
		str = ft_freetrim(str);
		cmds = ft_strsplit(str, ';');
		i = 0;
		while (cmds[i])
		{
			head = malloc(sizeof(t_command));
			use = ft_strtrim(cmds[i]);
			// temp = twsplit(use);
			temp = parseinput(cmds[i]);
			temp = check_file_agg(temp);
			if (temp[0] == NULL)
			{
				i++;
				continue;
			}
			checkenv(temp, vect);
			createcmds(head, temp);
			curr = head;
			while (curr)
			{
				ret = loopredir(curr,vect,shell);
				curr = curr->next;
				if (ret == -1)
					break;
			}
			dup2(shell->std_out, 1);
			dup2(shell->std_in, 0);
			free_cmd_list(head);
			i++;
			freedub(cmds);
			if (ret == -1)
				break ;
		}
		if (ret == -1)
			break ;
	}
	shellexit(shell);
	exit(0);
	return (0);
}
