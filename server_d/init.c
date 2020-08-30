/*
** init.c for init.c in /home/thenascrazy/tek2/Systeme_Unix/projet/PSU_2016_myirc/server_d
**
** Made by TheNasCrazy
** Login   <nacerdine.afou@epitech.eu>
**
** Started on  Sat Jun 10 19:07:12 2017 TheNasCrazy
** Last update Sun Jun 11 15:14:12 2017 Rayan
*/

#include "../include/irc.h"

int				init_serv(char **av, serv *serv)
{
  serv->cl_list = NULL;
  serv->port = atoi(av[1]);
  serv->s_in_size = sizeof(serv->s_in_cl);
  if (!(serv->pe = getprotobyname("TCP")))
    return (1);
  serv->s_in.sin_family = AF_INET;
  serv->s_in.sin_port = htons(serv->port);
  serv->s_in.sin_addr.s_addr = INADDR_ANY;
  if ((serv->fd = socket(AF_INET, SOCK_STREAM, serv->pe->p_proto)) == -1)
    return (1);
  if (bind(serv->fd, (const struct sockaddr *)&serv->s_in,
	   sizeof(serv->s_in)) == -1
      || listen(serv->fd, 42) == -1)
    {
      if (close(serv->fd) == -1)
	return (1);
      return (1);
    }
  serv->chanel = malloc(sizeof(char *));
  serv->chanel[0] = NULL;
  serv->chanel = add_chanel(serv->chanel, "default");
  return (0);
}

int				init_select(serv *serv)
{
  client			*p;

  p = serv->cl_list;
  FD_ZERO(&serv->readfds);
  FD_SET(serv->fd, &serv->readfds);
  while (p != NULL)
    {
      FD_SET(p->fd, &serv->readfds);
      p = p->next;
    }
}
