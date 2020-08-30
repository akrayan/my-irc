/*
** ft_cmd.c for ft_cmd.c in /home/thenascrazy/tek2/Systeme_Unix/projet/PSU_2016_myirc/server_d
**
** Made by TheNasCrazy
** Login   <nacerdine.afou@epitech.eu>
**
** Started on  Sat Jun 10 18:36:07 2017 TheNasCrazy
** Last update Sun Jun 11 20:40:46 2017 TheNasCrazy
*/

#include "../include/irc.h"

int				cmd_nick(client *cl, serv *serv, char **arg, char *buff)
{
  if (tab_len(arg) < 2)
    return (1);
  dprintf(cl->fd, ":%s NICK %s\r\n", cl->nick, arg[1]);
  if (cl->nick)
    free(cl->nick);
  cl->nick = strdup(arg[1]);
}

int				cmd_list(client *cl, serv *serv, char **arg, char *buff)
{
  int				j;

  dprintf(cl->fd, "321 Channels :\r\n");
  j = -1;
  while (serv->chanel[++j] != NULL)
    dprintf(cl->fd, "322 %s\r\n", serv->chanel[j]);
  dprintf(cl->fd, "323 Channels : End of /LIST\r\n");
}

int				cmd_join2(client *cl, serv *serv, char **arg, char *buff)
{
  client			*p;

  cl->chanel = add_chanel(cl->chanel, arg[1]);
  p = serv->cl_list;
  while (p != NULL)
    {
      if (is_in_tab(p->chanel, arg[1]))
	dprintf(p->fd, ":%s JOIN %s\r\n", cl->nick, arg[1]);
      p = p->next;
    }
  cmd_names(cl, serv, arg, buff);
}

int				cmd_join(client *cl, serv *serv, char **arg, char *buff)
{
  int				i;

  if (tab_len(arg) < 2)
    {
      dprintf(cl->fd, "461 Not enough parameters.\r\n");
      return (1);
    }
  i = -1;
  while (serv->chanel[++i] != NULL && strcmp(serv->chanel[i], arg[1]));
  if (serv->chanel[i] == NULL)
    serv->chanel = add_chanel(serv->chanel, arg[1]);
  i = -1;
  while (cl->chanel[++i] != NULL && strcmp(cl->chanel[i], arg[1]));
  if (cl->chanel[i] == NULL)
    cmd_join2(cl, serv, arg, buff);
  else
    dprintf(cl->fd, "You are already in the room.\r\n");
  return (0);
}

int				cmd_part(client *cl, serv *serv, char **arg, char *buff)
{
  client			*p;
  int				i;

  if (tab_len(arg) < 2)
    return (1);
  if (is_in_tab(cl->chanel, arg[1]))
    {
      p = serv->cl_list;
      while (p != NULL)
	{
	  if (is_in_tab(p->chanel, arg[1]))
	    dprintf(p->fd, ":%s PART %s\r\n", cl->nick, arg[1]);
	  p = p->next;
	}
      cl->chanel = sup_chanel(cl->chanel, arg[1]);
    }
}
