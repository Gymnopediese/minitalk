/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:58:13 by albaud            #+#    #+#             */
/*   Updated: 2022/10/28 13:18:15 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_byte
{
	char			byte[8];
	int				size;
}	t_byte;

typedef struct s_bytes
{
	t_byte			*bytes;
	int				size;
}	t_bytes;

int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	else if (power < 1)
		return (1);
	else
		return (nb * ft_recursive_power(nb, power - 1));
}

int	add_bit(int sig, int *c, int *indbite, int size)
{
	if (sig == SIGUSR2)
		*c += ft_recursive_power(2, *indbite);
	if (++*indbite == size)
	{
		*indbite = 0;
		return (1);
	}
	return (0);
}

void	add(int sig)
{
	static int	len;
	static int	gotlen;
	static int	indbite;
	static char	*toprint;
	static int	loop;

	if (!gotlen && add_bit(sig, &len, &indbite, 32))
		gotlen = 1;
	else if (gotlen)
	{
		if (toprint == 0)
			toprint = calloc(len + 1, 1);
		if (toprint == 0)
			return ;
		if (add_bit(sig, (int *)&toprint[loop], &indbite, 8)
			&& ++loop && loop == len)
		{
			toprint[loop] = 0;
			gotlen = 0;
			write(1, toprint, len);
			write(1, "\n", 1);
			free(toprint);
			toprint = 0;
			len = 0;
			loop = 0;
		}
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	usr1;
	struct sigaction	usr2;

	usr1.sa_handler = add;
	usr2.sa_handler = add;
	sigemptyset(&usr1.sa_mask);
	sigemptyset(&usr2.sa_mask);
	sigaddset(&usr1.sa_mask, SIGUSR1);
	sigaddset(&usr2.sa_mask, SIGUSR1);
	sigaction(SIGUSR1, &usr1, NULL);
	sigaction(SIGUSR2, &usr2, NULL);
	pid = getpid();
	printf("%i\n", pid);
	if (pid == -1)
		return (1);
	while (1)
	{
		pause();
	}
	return (0);
}

// void	append(int b)
// {
// 	int		loop;
// 	t_byte	*remp;

// 	loop = -1;
// 	if (to_print.bytes == 0)
// 	{
// 		to_print.bytes = malloc(sizeof(t_byte) * 2);
// 		if (!to_print.bytes)
// 			return ;
// 		to_print.size = 1;
// 		to_print.bytes[0].size = 0;
// 		to_print.bytes[1] = 0;
// 	}
// 	to_print.bytes[size][to_print.bytes[size].size++] = b;
// 	if (to_print.bytes[size].size == 8)
// 	{
// 		remp = malloc(sizeof(t_byte) * (++to_print.size + 1));
// 		if (remp == 0)
// 			return ;
// 		while (++loop)
// 			remp[loop] = to_print[loop]
// 		remp[++loop] = 0;
// 	}
// }
