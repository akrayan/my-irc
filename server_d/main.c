/*
** main.c for main.c in /home/thenascrazy/tek2/Systeme_Unix/projet/PSU_2016_myirc/server_d
**
** Made by TheNasCrazy
** Login   <nacerdine.afou@epitech.eu>
**
** Started on  Sat Jun 10 18:38:00 2017 TheNasCrazy
** Last update Sun Jun 11 21:55:28 2017 TheNasCrazy
*/

#include "../include/irc.h"

int				my_listlen(client *list)
{
  client			*tmp;
  int				i;

  i = 0;
  tmp = list;
  while (tmp != NULL)
    {
      tmp = tmp->next;
      i = i + 1;
    }
  return (i);
}

int				main(int ac, char **av)
{
  struct timeval		time;
  serv				serv;
  client			*p;
  int				nb;

  time.tv_sec = 0;
  time.tv_usec = 0;
  if (ac != 2)
    return (1);
  if (init_serv(av, &serv))
    return (1);
  while (42)
    {
      init_select(&serv);
      select(biggest_fd(serv.cl_list, serv.fd),
      &serv.readfds, NULL, NULL, NULL);
      if (check_select(&serv) == -1 && my_listlen(serv.cl_list) == 0)
	return (1);
    }
  if (close(serv.fd) == -1)
    return (1);
  return (0);
}
