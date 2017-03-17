#include "../headers/minishell.h"

int			setup_term(t_shell *shell)
{
	struct termios	new;

	if (tcgetattr(0, &shell->old) < 0)
		return (-1);
	new = shell->old;
	new.c_lflag &= ~(ECHO | ICANON);
	// new.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

	new.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
	| INLCR | IGNCR | ICRNL | IXON);
	new.c_cflag &= ~(CSIZE | PARENB);
	new.c_cflag |= CS8;
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSAFLUSH, &new) < 0)
		return (-1);
	shell->now = &new;
	return (1);
}
