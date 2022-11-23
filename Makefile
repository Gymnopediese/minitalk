# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaud <albaud@student.42lausanne.ch>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/27 16:05:24 by albaud            #+#    #+#              #
#    Updated: 2022/10/28 01:42:31 by albaud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SE			= server
CL			= client
CLFI		= fidel_client
SEF			= server.c
CLF			= client.c
CLFIF		= client_fidel.c
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

all		: $(CL) $(SE)

.c.o 	:
		${CC} ${CFLAGS} -c ${<:.c=.o}

$(CL)	: 
		${CC} ${CFLAGS} -o ${CL} ${CLF} 
$(SE)	: 
		${CC} ${CFLAGS} -o ${SE} ${SEF}
$(CLFI)	: 
	${CC} ${CFLAGS} -o ${CLFI} ${CLFIF} 

bonus	: $(CLFI) $(SE)

clean	:
		rm -f ${OBJS}
		
fclean	:	clean
		rm -f $(CL) $(SE) $(CLFI)
re:		fclean all

reb:		fclean bonus