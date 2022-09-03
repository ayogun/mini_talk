/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 00:44:06 by yogun             #+#    #+#             */
/*   Updated: 2022/09/03 16:52:40 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

// kill() is used to send signal to process
void	send_signals(char *message, int pid)
{
   int	i;
   int	shift;

   shift = -1;
   i = 0;
   while (message[i])
   {
   	while (++shift < 8)
   	{
   		if (message[i] & (0x80 >> shift))
   		{
   			if (kill(pid, SIGUSR2) == -1)
   				exit(1);
   		}
   		else
   		{
   			if (kill(pid, SIGUSR1) == -1)
   				exit (1);
   		}
   		usleep(3);
   	}
   	i++;
   }
}

int	main(int argc, char *argv[])
{
   int		pid;

   if (argc != 3)
   {
   	printf("client: invalid arguments\n");
   	printf("\tcorrect format [./%s SERVER_PID MESSAGE\n]", argv[0]);
   	exit(EXIT_FAILURE);
   }
   pid = atoi(argv[1]);
   send_signals(argv[2], pid);
   return (0);
}