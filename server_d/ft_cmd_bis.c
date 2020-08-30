/*
** ft_cmd_bis.c for ft_cmd_bis.c in /home/thenascrazy/tek2/Systeme_Unix/projet/PSU_2016_myirc/server_d
**
** Made by TheNasCrazy
** Login   <nacerdine.afou@epitech.eu>
**
** Started on  Sat Jun 10 18:40:26 2017 TheNasCrazy
** Last update Sun Jun 11 20:32:52 2017 TheNasCrazy
*/

#include "../include/irc.h"

int				cmd_users(client *cl, serv *serv, char **arg, char *buff)
{
  client			*p;

  dprintf(cl->fd, "392 USERS\r\n");
  p = serv->cl_list;
  while (p != NULL)
    {
      dprintf(cl->fd, "393 %s\r\n", p->nick);
      p = p->next;
    }
  dprintf(cl->fd, "394 end of /USERS\r\n");
}

int				cmd_names(client *cl, serv *serv, char **arg, char *buff)
{
  client			*p;

  if (tab_len(arg) < 2)
    {
      dprintf(cl->fd, "USAGE \"/names $chanel\"\r\n");
      return (1);
    }
  if (is_in_tab(serv->chanel, arg[1]) == 0)
    return (1);
  dprintf(cl->fd, "353 %s : NAMES ", arg[1]);
  p = serv->cl_list;
  while (p != NULL)
    {
      if (p->chanel[0] != NULL
	  && is_in_tab(p->chanel, arg[1]))
	dprintf(cl->fd, "%s  ", p->nick);
      p = p->next;
    }
  dprintf(cl->fd, "\r\n366 %s :End of /NAMES list\r\n", arg[1]);
}

int				cmd_accept(client *cl, serv *serv, char **arg, char *buff)
{
}

int				cmd_msg(client *cl, serv *serv, char **arg, char *buff)
{
  client			*p;
  int				i;

  if (tab_len(arg) < 3)
    {
      dprintf(cl->fd, "461 Not enough parameters.\r\n");
      return (1);
    }
  p = serv->cl_list;
  while (p != NULL && strcmp(p->nick, arg[1]) != 0)
    p = p->next;
  if (p == NULL)
    return (0);
  dprintf(p->fd, "PRIVMSG %s :", arg[1]);
  i = 1;
  while (arg[++i] != NULL)
    {
      if (arg[i + 1] != NULL)
	dprintf(p->fd, "%s ", arg[i]);
      else
	dprintf(p->fd, "%s\r\n", arg[i]);
    }
}

int				cmd_unknow(client *cl, serv *serv, char **arg, char *buff)
{
  client			*p;

  printf("un client a fait une cmd inconue\n");
  p = serv->cl_list;
  if (cl->chanel[0] != NULL)
    {
      while (p != NULL)
	{
	  if ((p != cl && p->chanel[0] != NULL &&
	       is_in_tab(p->chanel, cl->chanel[tab_len(cl->chanel) - 1])))
	    dprintf(p->fd, "[%s] %s\r\n", cl->nick, buff);
	  p = p->next;
	}
    }
}
