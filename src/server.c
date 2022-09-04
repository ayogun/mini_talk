/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 00:43:56 by yogun             #+#    #+#             */
/*   Updated: 2022/09/04 13:03:49 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

// Why would I use signal while there is a better version of it which is sigaction YAY.
// Sigaction is more ortable.
static void	action(int sig, siginfo_t *info, void *context)
{
	static int				i = 0;
	static unsigned char	c = 0;
	pid_t					pid_client;

	(void)context;
	if (info->si_pid)
		pid_client = info->si_pid;
	c = c | (sig == SIGUSR1);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(pid_client, SIGUSR1);
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
		kill(pid_client, SIGUSR2);
	}
	else
		c = c << 1;
}

// If SA_SIGINFO is set and the signal is caught, the signal-catching function shall be entered as:
// void func(int signo, siginfo_t *info, void *context);
// STDOUT_FILENO	1	/* standard output file descriptor */
int	main(void)
{
	struct sigaction	sa;
	pid_t				pid_server;

	pid_server = getpid();
	ft_putstr_fd("Server PID: ", STDOUT_FILENO);
	ft_putnbr_fd(pid_server, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	sa.sa_sigaction = action;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
   ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}


