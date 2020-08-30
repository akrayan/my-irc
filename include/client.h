/*
** client.h for client.h in /home/thenascrazy/tek2/Systeme_Unix/projet/PSU_2016_myirc
**
** Made by TheNasCrazy
** Login   <nacerdine.afou@epitech.eu>
**
** Started on  Sun Jun 11 16:54:50 2017 TheNasCrazy
** Last update Sun Jun 11 19:50:07 2017 TheNasCrazy
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string.h>
# include "get_next_line.h"

typedef struct	s_client
{
  struct protoent	*pe;
  int			fd_server;
  struct sockaddr_in	s_in;
  int			port;
  char			*ip;
  char			*s;
  char			*s_server;
  fd_set		readfds;
  fd_set		writefds;
  fd_set		excpfds;
}		t_client;

#endif /* !CLIENT_H_ */
