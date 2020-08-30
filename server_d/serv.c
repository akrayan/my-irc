/*
** serv.c for serv.c in /home/thenascrazy/tek2/Systeme_Unix/projet/PSU_2016_myirc/server_d
**
** Made by TheNasCrazy
** Login   <nacerdine.afou@epitech.eu>
**
** Started on  Sun Jun 11 20:41:19 2017 TheNasCrazy
** Last update Sun Jun 11 21:51:45 2017 TheNasCrazy
*/

#include "../include/irc.h"

int				biggest_fd(client *cl_list, int fd)
{
  client			*p;
  int				r;

  r = 0;
  p = cl_list;
  while (p != NULL)
    {
      if (r < p->fd)
	r = p->fd;
      p = p->next;
    }
  if (r < fd)
    r = fd;
  return (r + 1);
}

int				id_cmd(char **arg)
{
  int				i;
  int				j;
  char				*tab[10];

  tab[0] = "SERVER";
  tab[1] = "NICK";
  tab[2] = "LIST";
  tab[3] = "JOIN";
  tab[4] = "PART";
  tab[5] = "USERS";
  tab[6] = "NAMES";
  tab[7] = "ACCEPT";
  tab[8] = "PRIVMSG";
  tab[9] = "QUIT";
  i = -1;
  while (++i < 10 && strcmp(tab[i], arg[0]) != 0);
  printf("%d       %s\n", i, arg[0]);
  return (i);
}

int				check_cmd(client *cl, serv *server, char *s)
{
  int				(*tab[11])(client *cl, serv *se, char **arg, char *buff);
  char				**arg;

  tab[0] = cmd_server;
  tab[1] = cmd_nick;
  tab[2] = cmd_list;
  tab[3] = cmd_join;
  tab[4] = cmd_part;
  tab[5] = cmd_users;
  tab[6] = cmd_names;
  tab[7] = cmd_accept;
  tab[8] = cmd_msg;
  tab[9] = cmd_quit;
  tab[10] = cmd_unknow;
  arg = str_to_wordtab(s, ' ');
  (*tab[id_cmd(arg)])(cl, server, arg, s);
}

int				handle_client(client *cl, serv *serv)
{
  client			*p;
  char				buff[512];
  int				len;

  len = read(cl->fd, buff, 511);
  if (len <= 0)
    {
      write(2, "error on read\n", strlen("error on read\n"));
      close (cl->fd);
      serv->cl_list = sup_client(serv->cl_list, cl);
      return (-1);
    }
  if (buff[len - 1] == '\n')
    buff[len - 1] = 0;
  buff[len] = 0;
  check_cmd(cl, serv, buff);
}

int				check_select(serv *serv)
{
  client			*p;
  int				cl_fd;

  if (FD_ISSET(serv->fd, &serv->readfds))
    {
      if ((cl_fd = accept(serv->fd, (struct sockaddr *) &serv->s_in_cl,
			  &serv->s_in_size)) == -1)
	{
	  if (close(serv->fd) == -1)
	    return (1);
	  return (1);
	}
      serv->cl_list = add_client(serv->cl_list, cl_fd,
      inet_ntoa(serv->s_in_cl.sin_addr));
      dprintf(cl_fd, "001 Welcome to our IRC.\r\n");
    }
  p = serv->cl_list;
  while (p != NULL)
    {
      if (FD_ISSET(p->fd, &serv->readfds))
	if (handle_client(p, serv) == -1)
	  return (-1);
      p = p->next;
    }
  return (0);
}
