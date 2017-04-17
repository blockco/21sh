/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassafa <rpassafa@student.42.us>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 00:38:54 by rpassafa          #+#    #+#             */
/*   Updated: 2017/02/20 16:11:10 by rpassafa         ###   ########.us       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/uio.h>
# include <limits.h>
# include <termios.h>
# include <termcap.h>
# include <term.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <signal.h>
# include <sys/types.h>
# include "../libft/libft.h"
# include "vector.h"
# include <signal.h>
# define ENDL '\n'
# define BUFF_SIZE 4

# define CLEAR				tputs(tgetstr("cl", NULL), 1, ft_putchar)
# define STR_CURSOR_MV		tputs(tgetstr("ti", NULL), 1, ft_putchar)
# define END_CURSOR_MV		tputs(tgetstr("te", NULL), 1, ft_putchar)
# define LINE				tputs(tgetstr("cr", NULL), 1, ft_putchar)
# define SCREEN				tputs(tgetstr("ho", NULL), 1, ft_putchar)
# define DOWN				tputs(tgetstr("do", NULL), 1, ft_putchar)
# define UP					tputs(tgetstr("up", NULL), 1, ft_putchar)
# define RIGHT				tputs(tgetstr("nd", NULL), 1, ft_putchar)
# define LEFT				tputs(tgetstr("le", NULL), 1, ft_putchar)
# define DEL_MODE_ON		tputs(tgetstr("dm", NULL), 1, ft_putchar)
# define DEL_CHAR			tputs(tgetstr("dc", NULL), 1, ft_putchar)
# define DEL_MODE_OFF		tputs(tgetstr("ed", NULL), 1, ft_putchar)
# define INSERT_MODE_ON		tputs(tgetstr("im", NULL), 1, ft_putchar)
# define INSERT_CHAR		tputs(tgetstr("ic", NULL), 1, ft_putchar)
# define INSERT_MODE_OFF	tputs(tgetstr("ei", NULL), 1, ft_putchar)
# define DL					tputs(tgetstr("dl", NULL), 1, ft_putchar)
# define CLEAR_LN			tputs(tgetstr("cd", NULL), 1, ft_putchar)
# define LEFT_LN			tputs(tgetstr("ll", NULL), 1, ft_putchar)
# define STR_LEFT			tputs(tgetstr("cr", NULL), 1, ft_putchar)
# define WRAP_TERM			tputs(tgetstr("ho", NULL), 1, ft_putchar)

# define KEYS_ON			tputs(tgetstr("ks", NULL), 1, ft_putchar)
# define KEYS_OFF			tputs(tgetstr("ke", NULL), 1, ft_putchar)

# define TC_HID_CURSOR		tputs(tgetstr("vi", NULL), 1, ft_putchar)
# define TC_STR_MV_CURSOR	tputs(tgetstr("ti", NULL), 1, ft_putchar)

# define LEFT_MARGIN		tputs(tgetstr("rs", NULL), 1, ft_putchar)


# define C_NORMAL			ft_putstr_fd("\e[0;39;48;5;239m", 2)
# define C_CURSOR			ft_putstr_fd("\e[4;39;48;5;239m", 2)
# define C_SELECTED			ft_putstr_fd("\e[0;30;107m", 2)
# define C_BOTH				ft_putstr_fd("\e[4;30;107m", 2)
# define COLOR_NOPE			ft_putstr_fd("\e[0m", 2)

# define K_UP				4283163
# define K_DOWN				4348699
# define K_LEFT				4479771
# define K_RIGHT			4414235
# define K_HOME				4741915
# define K_END				4610843
# define K_ESC				27
# define K_ENTER			10
# define K_BACKSP			127
# define K_DEL				2117294875
# define K_TAB				9
# define K_SPACE			32
# define K_F1				5263131
# define K_F2				5328667

# define C_UP				"\[A"
# define C_LEFT				"\[D"
# define C_RIGHT			"\[C"
# define C_DOWN				"\[B"


typedef struct	s_command
{
	char 				**args;
	int 				pipe;
	struct s_file		*head_file;
	struct s_command 	*next;
}						t_command;

typedef struct	s_file
{
	t_command			*parent;
	struct s_file		*next;
	char 				*file;
	int 				redir;
}						t_file;


typedef struct s_lineman
{
	int linespot;
	int size;
	int spot_hist;
	int dq;
}				t_lineman;

typedef struct	s_shell
{
	struct termios	old;
	struct termios	*now;
	int				endl;
	t_vector		*history;
	t_vector		*sorted_h;
	t_command		*cmd;
	t_lineman		*lineinfo;
}				t_shell;

typedef struct	s_parse
{
	char		**retstr;
	int			start;
	int			end;
	int			dq;
	int			count;
	int			i;
}				t_parse;

char			*read_tmp(t_shell *shell);
void			storeenv(t_vector *vect, char **envp);
char			*subof(char *str, int sub);
char			**getbins(t_vector *vect);
int				execprog(char *str, char **bins, char **temp, t_vector *vect);
int				countarray(char **lst);
char			*checkbin(char *prog, char *path);
void			getenvvar(t_vector *vect, char *str);
int				inputsize(char *str);
int				trimsome(char *str, int i);
char			*my_word_builder(char const *str, unsigned int *index);
char			**my_ft_strsplit(char const *s);
void			freedub(char **str);
char			**parseinput(char *str);
void			runprog(char *test, char **temp, t_vector *vect);
void			getenvvar(t_vector *vect, char *str);
void			getenv_b(t_vector *vect);
char			*dupenvvar(t_vector *vect, char *str);
void			checkenv(char **temp, t_vector *vect);
int				runbuilt(char **temp, t_vector *vect);
char			*findenvvar(t_vector *vect, char *str);
void			changedirs(char *path, t_vector *vect);
int				findenvvarint(t_vector *vect, char *str);
void			setenv_b(char *key, char *val, t_vector *vect);
void			unsetenv_b(char *key, t_vector *vect);
void			echo_b(char **temp);
void			gohome(t_vector *vect, char *cwd);
void			goback(t_vector *vect, char *cwd);
void			print_interp();
char			**cpenv_b(t_vector *vect);
void			changeold(int ret, t_vector *vect, char *cwd, int i);
void			checkchange(int i, char *path);
char			*til_b(char *path, t_vector *vect);
void			ft_til(t_vector *vect, char *path, char *cwd);
void			checkenv(char **temp, t_vector *vect);
char			**parseinput(char *str);
int				checklocsp(char *test, char **temp, t_vector *vect);


void			insert_char(char *c);
void			insert_str(char *c);
int				setup_term(t_shell *shell);
void			initshellstruct(t_shell *shell);
void 			termresetline(t_shell *shell);

//checking data
int check_char(char *data, t_shell *shell);

//line management
char *cop_begin(char *ret, int spot);
char *copend(char *ret, int spot);
char *addtobuff(t_shell *shell, char *ret, char *str1);
char *del_fun(char *ret, int spot);

//redirect parse
void createcmds(t_command *head, char **temp);
int findargs(char **temp);
int isredir(char *str);

#endif
