/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_fidel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:58:13 by albaud            #+#    #+#             */
/*   Updated: 2022/10/28 01:51:32 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char	*message;

void	send_byte(int pid, char c)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (c & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c >> 1;
		usleep(100);
	}
}

void	send_string(int pid, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		send_byte(pid, str[i]);
}

void	success(int sig)
{
	(void) sig;
	printf("succeed to send the message\n");
}

void	failed(int sig)
{
	(void) sig;
	printf("failed to send the message\n");
}

int	main(int argc, char **argv)
{
	int		pid;
	char	msg[1000];
	int		len;
	
	if (argc != 3)
	{
		printf("fidel_client: usage: ./fidel_client pid username");
		return (1);
	}
	pid = atoi(argv[1]);
	strcpy(msg, argv[2]);
	len = strlen(argv[2]);
	msg[len] = ':';
	msg[++len] = ' ';
	++len;
	while (1)
	{
		printf(">> ");
		msg[read(STDIN_FILENO, &msg[len], 1000)] = 0;
		send_byte(pid, (char)strlen(msg));
		send_string(pid, msg);
	}
}
