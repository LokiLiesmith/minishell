#include "minishell.h"

static void	handle_sigint(int signum)
{
	g_exit_status = signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_setup(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

// void	set_child_signals(void)
// {
// 	struct sigaction	sa;

// 	ft_memset(&sa, 0, sizeof(sa));
// 	sa.sa_handler = SIG_DFL;
// 	sigaction(SIGINT, &sa, NULL);

// }