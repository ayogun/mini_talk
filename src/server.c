/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 00:43:56 by yogun             #+#    #+#             */
/*   Updated: 2022/09/03 22:34:40 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

// Why would I use signal while there is a better version of it which is sigaction YAY
void	handler_sigusr(int signum)
{
   static char	c = 0xFF;
   static int	bits = 0;

   if (signum == SIGUSR1)
   {
   	printf("0");
   	c ^= 0x80 >> bits;
   }
   else if (signum == SIGUSR2)
   {
   	printf("1");
   	c |= 0x80 >> bits;
   }
   bits++;
   if (bits == 8)
   {
   	printf("-> %c\n", c);
   	bits = 0;
   	c = 0xFF;
   }
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
	while (1)
		pause();
	return (0);
}


